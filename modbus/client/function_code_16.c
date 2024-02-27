#include <modbus/modbus.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void function_code_16(modbus_t *context)
{

    int start_registers_address = 0;
    int number_of_registers = 0;
    int value = 0;

    printf("<Start register address> <Number of register> <value>\n");
    scanf("%d %d %d", &start_registers_address, &number_of_registers, &value);

    if (start_registers_address < 0 || start_registers_address + number_of_registers > 125)
    {
        printf("Exceeding the scope error\n");
        return;
    }
    if (value != 0 && value != 1)
    {
        printf("Value must be 0 or 1\n");
        return;
    }

    uint16_t registers_values[start_registers_address];

    for (int i = start_registers_address; i < start_registers_address + number_of_registers; i++)
    {
        registers_values[i] = value;
    }

    if (modbus_write_registers(context, start_registers_address, number_of_registers, registers_values) == -1) {
        fprintf(stderr, "Write Multiple Holding Registers failed: %s\n", modbus_strerror(errno));
        modbus_close(context);
        modbus_free(context);
        exit(1);
    }

    printf("Write Multiple Holding Registers successful.\n");
}