#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus/modbus.h>

#define LOOP 1         // �ݺ� Ƚ��
#define TOTAL_COILS 10 // ������ ����Ʈ ��

void function_code_01(char *argv[])
{
    // Modbus TCP ������ ����
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

    // ������ ������ �뿪���� ����
    uint8_t rd_coils[TOTAL_COILS];

    // Modbus �Լ� �ڵ� 01�� ����Ͽ� Coils ���� �б�
    int i, rc;
    for (i = 0; i < LOOP; i++)
    {
        rc = modbus_read_bits(context, 0, TOTAL_COILS, rd_coils);
        if (rc == -1)
        {
            fprintf(stderr, "Read coils failed: %s\n", modbus_strerror(errno));
            break;
        }

        // ���� Coils ���� ���
        printf("Coils values read: ");
        for (int j = 0; j < TOTAL_COILS; j++)
        {
            printf("%x ", rd_coils[j]);
        }
        printf("\n");
    }

    // ���� ����
    modbus_close(context);
    modbus_free(context);
}
