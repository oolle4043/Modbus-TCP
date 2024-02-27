#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus/modbus.h>

void function_code_01(modbus_t *context)
{
    int start_address = 0;
    int total_colis = 0;

    printf("<Start address> <Total coils>\n");
    scanf("%d %d", &start_address, &total_colis);

    if (start_address < 0 || total_colis > 2000)
    {
        printf("Exceeding the scope error\n");
        return;
    }

    uint8_t rd_coils[total_colis];

    int rc;

    rc = modbus_read_bits(context, start_address, total_colis, rd_coils);
    if (rc == -1)
    {
        fprintf(stderr, "Read coils failed: %s\n", modbus_strerror(errno));
    }
    else
    {
        printf("Coils values read: ");

        for (int i = 0; i < total_colis; i++)
        {
            printf("%d ", rd_coils[i]);
        }
        printf("\n");
    }
}
