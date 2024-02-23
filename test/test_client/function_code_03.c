/*
Function Code 03 Read Holding Registers
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus/modbus.h>

#define LOOP 1        // �ݺ� Ƚ��
#define TOTAL_REGISTERS 10 // ������ ����Ʈ ��

void function_code_03(char *argv[])
{
    // Modbus TCP ������ ����
    modbus_t *context = modbus_new_tcp(argv[1], atoi(argv[2]));
    if (modbus_connect(context) == -1)
    {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(context);
    }

    // ������ ������ �뿪���� ����
    uint16_t rd_registers[TOTAL_REGISTERS];

    // Modbus �Լ� �ڵ� 03�� ����Ͽ� Holding Registers ���� �б�
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
        // ���� Holding Registers ���� ���
        printf("Holding Registers values read: ");
        for (int j = 0; j < TOTAL_REGISTERS; j++)
        {
            printf("%x ", rd_registers[j]);
        }
        printf("\n");
    }
    // ���� ����
    modbus_close(context);
    modbus_free(context);
}