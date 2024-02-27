#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <modbus/modbus.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

#include "modbus_global.h"
#include "close_sigint.h"

#define NUM_BITS MODBUS_MAX_READ_BITS
#define NUM_REGISTERS MODBUS_MAX_READ_REGISTERS

void run(int argc, char *argv[])
{
    uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
    int master_socket;
    int rc;
    fd_set reference_set;
    fd_set read_set;
    int fdmax;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    ctx = modbus_new_tcp(argv[1], atoi(argv[2]));

    mb_mapping = modbus_mapping_new(MODBUS_MAX_READ_BITS, MODBUS_MAX_READ_BITS, MODBUS_MAX_READ_REGISTERS, MODBUS_MAX_READ_REGISTERS);

    if (mb_mapping == NULL)
    {
        fprintf(stderr, "Failed to allocate the mapping: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        exit(1);
    }

    server_socket = modbus_tcp_listen(ctx, MAX_CLIENT); // 소캣 바인딩
    if (server_socket == -1)
    {
        fprintf(stderr, "Unable to listen TCP connection\n");
        modbus_free(ctx);
        close_sigint(1);
    }

    signal(SIGINT, close_sigint); // SIGINT(Ctrl + C) 시그널 처리 등록

    FD_ZERO(&reference_set);               // reference_set 파일 디스크립터를 초기화
    FD_SET(server_socket, &reference_set); // server_socket 파일 디스크립터를 reference_set에 추가

    fdmax = server_socket;

    while (1)
    {
        read_set = reference_set;
        if (select(fdmax + 1, &read_set, NULL, NULL, NULL) == -1) // 파일 디스크립터의 상태 확인
        {
            perror("Server select() failure.");
            close_sigint(1);
        }

        // 파일 디스크립터 집합에 있는 모든 소켓을 반복적으로 확인
        for (master_socket = 0; master_socket <= fdmax; master_socket++)
        {
            if (!FD_ISSET(master_socket, &read_set))
            {
                continue;
            }
            if (master_socket == server_socket) // 참일경우 클라이언트 연결 수락
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
                    FD_SET(newfd, &reference_set);

                    if (newfd > fdmax)
                    {
                        fdmax = newfd;
                    }
                    printf("New connection from %s:%d on socket %d\n", inet_ntoa(clientaddr.sin_addr), clientaddr.sin_port, newfd);
                    printf("\n");
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
                    printf("Connection closed on socket %d\n", master_socket);
                    close(master_socket);

                    FD_CLR(master_socket, &reference_set); // 파일 디스크립터를 제거

                    if (master_socket == fdmax)
                    {
                        fdmax--;
                    }
                }
                printf("Transaction ID: %x %x\n", query[0], query[1]);
                printf("Protocol ID: %x %x\n", query[2], query[3]);
                printf("Length: %x %x\n", query[4], query[5]);
                printf("Unit ID: %x\n", query[6]);
                printf("Function Code: %x\n", query[7]);
                printf("Data: ");

                if (query[7] == 1 || query[7] == 2 || query[7] == 5 || query[7] == 15)
                {
                    for (size_t i = 0; i < NUM_BITS; i++)
                    {
                        printf("%d ", mb_mapping->tab_bits[i]);
                    }
                }
                else if (query[7] == 4 || query[7] == 3 || query[7] == 6 || query[7] == 16)
                {
                    for (size_t i = 0; i < NUM_REGISTERS; i++)
                    {
                        printf("%u ", mb_mapping->tab_registers[i]);
                    }
                }

                printf("\n");
            }
        }
    }
}