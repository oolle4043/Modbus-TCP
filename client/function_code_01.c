#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus/modbus.h>

#define LOOP 1         // 반복 횟수
#define TOTAL_COILS 10 // 데이터 포인트 수

void function_code_01(char *argv[])
{
    // Modbus TCP 서버에 연결
    modbus_t *context = modbus_new_tcp(argv[1], atoi(argv[2]));
    if (context == NULL)
    {
        fprintf(stderr, "Failed to create Modbus context: %s\n", modbus_strerror(errno));
        return;
    }

    if (modbus_connect(context) == -1)
    {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(context);
        return;
    }

    // 측정할 데이터 대역폭을 정의
    uint8_t rd_coils[TOTAL_COILS];

    // Modbus 함수 코드 01을 사용하여 Coils 값을 읽기
    int i, rc;
    for (i = 0; i < LOOP; i++)
    {
        rc = modbus_read_bits(context, 0, TOTAL_COILS, rd_coils);
        if (rc == -1)
        {
            fprintf(stderr, "Read coils failed: %s\n", modbus_strerror(errno));
            break;
        }

        // 읽은 Coils 값을 출력
        printf("Coils values read: ");
        for (int j = 0; j < TOTAL_COILS; j++)
        {
            printf("%x ", rd_coils[j]);
        }
        printf("\n");
    }

    // 연결 종료
    modbus_close(context);
    modbus_free(context);
}
