#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <modbus/modbus.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <time.h>

#define NB_CONNECTION 5

static modbus_t *ctx = NULL;
static modbus_mapping_t *mb_mapping;
static int server_socket = -1;

static void close_sigint(int dummy);

int main(int argc, char *argv[])
{
    uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
    int master_socket;
    int rc;
    fd_set refset;
    fd_set rdset;
    int fdmax; // 최대 파일 설명자 번호

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    ctx = modbus_new_tcp(argv[1], atoi(argv[2]));

    mb_mapping = modbus_mapping_new(MODBUS_MAX_READ_BITS, 0, MODBUS_MAX_READ_REGISTERS, 0);
    if (mb_mapping == NULL)
    {
        fprintf(stderr, "Failed to allocate the mapping: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }

    // 코일 및 레지스터 값 초기화
    srand(time(NULL)); // 난수 발생기 초기화

    // 코일의 초기값 설정 (0 또는 1)
    for (int i = 0; i < MODBUS_MAX_READ_BITS; i++)
    {
        mb_mapping->tab_bits[i] = rand() % 2;
    }

    // 레지스터의 초기값 설정 (0부터 65535 사이의 값)
    for (int i = 0; i < MODBUS_MAX_READ_REGISTERS; i++)
    {
        mb_mapping->tab_registers[i] = rand() % 65536;
    }

    server_socket = modbus_tcp_listen(ctx, NB_CONNECTION);
    if (server_socket == -1)
    {
        fprintf(stderr, "Unable to listen TCP connection\n");
        modbus_free(ctx);
        return -1;
    }

    signal(SIGINT, close_sigint);

    FD_ZERO(&refset);               // refset 파일 디스크립터를 초기화
    FD_SET(server_socket, &refset); // server_socket 파일 디스크립터를 refset에 추가

    fdmax = server_socket;

    while (1)
    {
        rdset = refset;
        if (select(fdmax + 1, &rdset, NULL, NULL, NULL) == -1)
        {
            perror("Server select() failure.");
            close_sigint(1);
        }

        // 파일 디스크립터 집합에 있는 모든 소켓을 반복적으로 확인
        for (master_socket = 0; master_socket <= fdmax; master_socket++)
        {

            if (!FD_ISSET(master_socket, &rdset))
            {
                continue;
            }

            if (master_socket == server_socket)
            {
                socklen_t addrlen;
                struct sockaddr_in clientaddr;
                int newfd;

                addrlen = sizeof(clientaddr);
                memset(&clientaddr, 0, sizeof(clientaddr));
                newfd = accept(server_socket, (struct sockaddr *)&clientaddr, &addrlen);
                if (newfd == -1)
                {
                    perror("Server accept() error");
                }
                else
                {
                    FD_SET(newfd, &refset);

                    if (newfd > fdmax)
                    {
                        fdmax = newfd;
                    }
                    printf("New connection from %s:%d on socket %d\n", inet_ntoa(clientaddr.sin_addr), clientaddr.sin_port, newfd);
                }
            }
            else
            {
                modbus_set_socket(ctx, master_socket);
                rc = modbus_receive(ctx, query);
                if (rc > 0)
                {
                    modbus_reply(ctx, query, rc, mb_mapping);
                }
                else if (rc == -1)
                {
                    uint8_t Request_function_code = query[7];

                    switch (Request_function_code)
                    {
                    case 1:
                        printf("Request function code: %d\n", Request_function_code);
                        printf("Coils values: ");
                        for (int i = 0; i < 10; i++)
                        {
                            printf("%x ", mb_mapping->tab_bits[i]);
                        }
                        break;
                    case 3:
                        printf("Request function code: %d\n", Request_function_code);
                        printf("Holding Registers values: ");
                        for (int i = 0; i < 10; i++)
                        {
                            printf("%x ", mb_mapping->tab_registers[i]);
                        }
                    default:
                        break;
                    }
                    printf("\n");
                    printf("Connection closed on socket %d\n", master_socket);
                    close(master_socket);

                    FD_CLR(master_socket, &refset); // 특정 파일 디스크립터를 제거

                    if (master_socket == fdmax)
                    {
                        fdmax--;
                    }
                }
            }
        }
    }
    return 0;
}

static void close_sigint(int dummy)
{
    if (server_socket != -1)
    {
        close(server_socket);
    }
    modbus_free(ctx);
    modbus_mapping_free(mb_mapping);

    exit(dummy);
}

/*


*/