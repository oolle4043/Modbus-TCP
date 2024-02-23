/*
Function Code 03 Read Holding Registers
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus/modbus.h>

#define LOOP 1        // 반복 횟수
#define TOTAL_REGISTERS 10 // 데이터 포인트 수

void function_code_03(char *argv[])
{
    // Modbus TCP 서버에 연결
    modbus_t *context = modbus_new_tcp(argv[1], atoi(argv[2]));
    if (modbus_connect(context) == -1)
    {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(context);
    }

    // 측정할 데이터 대역폭을 정의
    uint16_t rd_registers[TOTAL_REGISTERS];

    // Modbus 함수 코드 03을 사용하여 Holding Registers 값을 읽기
    int i, rc;

    for (i = 0; i < LOOP; i++)
    {
        rc = modbus_read_registers(context, 0, TOTAL_REGISTERS, rd_registers);
        if (rc == -1)
        {
            fprintf(stderr, "%s\n", modbus_strerror(errno));
            modbus_close(context);
            modbus_free(context);
        }
        // 읽은 Holding Registers 값을 출력
        printf("Holding Registers values read: ");
        for (int j = 0; j < TOTAL_REGISTERS; j++)
        {
            printf("%x ", rd_registers[j]);
        }
        printf("\n");
    }
    // 연결 종료
    modbus_close(context);
    modbus_free(context);
}