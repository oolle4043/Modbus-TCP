#include <modbus/modbus.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void function_code_05(modbus_t *context)
{
    int coil_address = 0;
    int value = 0;

    printf("<Coil address> <Value>\n");
    scanf("%d %d", &coil_address, &value);

    if (coil_address < 0 ||coil_address > 2000)
    {
        printf("Exceeding the scope error\n");
        return;
    }
    if (value != 0 && value != 1)
    {
        printf("Value must be 0 or 1\n");
        return;
    }

    if (value != 0 && value != 1)
    {
        fprintf(stderr, "Value must be 0 or 1\n");
        return;
    }

    if (modbus_write_bit(context, coil_address, value) == -1)
    {
        fprintf(stderr, "Failed to write single coil: %s\n", modbus_strerror(errno));
        modbus_close(context);
        modbus_free(context);
        exit(1);
    }

    printf("Write successful\n");
}