#include <modbus/modbus.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void function_code_06(modbus_t *context)
{
    int register_address = 0;
    int value = 0;

    printf("<Registser address> <Value>\n");
    scanf("%d %d", &register_address, &value);

    if (register_address > 125)
    {
        printf("Exceeding the scope error\n");
        return;
    }
    if (value != 0 && value != 1)
    {
        printf("Value must be 0 or 1\n");
        return;
    }

    if (modbus_write_register(context, register_address, value) == -1)
    {
        fprintf(stderr, "Failed to write single register: %s\n", modbus_strerror(errno));
        modbus_close(context);
        modbus_free(context);
        exit(1);
    }

    printf("Write successful\n");
}