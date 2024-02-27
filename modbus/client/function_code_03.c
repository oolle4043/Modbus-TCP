#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus/modbus.h>

void function_code_03(modbus_t *context)
{
    int start_address = 0;
    int total_registers = 0;

    printf("<Start address> <Total registers>\n");
    scanf("%d %d", &start_address, &total_registers);

    if (start_address < 0 || total_registers > 125)
    {
        printf("Exceeding the scope error\n");
        return;
    }

    uint16_t rd_registers[total_registers];

    int rr;
    rr = modbus_read_registers(context, start_address, total_registers, rd_registers); // context 구조체, 시작주소, 읽어올 레지스터 수, 읽어온 레지스터 값들을 저장 할 배열
    if (rr == -1)
    {
        fprintf(stderr, "%s\n", modbus_strerror(errno));
        modbus_free(context);
        exit(1);
    }
    printf("Holding Registers values read: ");
    for (int i = 0; i < total_registers; i++)
    {
        printf("%u ", rd_registers[i]);
    }
    printf("\n");
}
