#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus/modbus.h>

void function_code_04(modbus_t *context)
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

    uint16_t input_registers[total_registers];

    int rr = modbus_read_input_registers(context, start_address, total_registers, input_registers);

    if (rr == -1)
    {
        fprintf(stderr, "Read input registers failed: %s\n", modbus_strerror(errno));
        modbus_close(context);
        modbus_free(context);
        exit(1);
    }

    printf("Input registers: ");
    for (int i = 0; i < total_registers; i++)
    {
        printf("%d ", input_registers[i]);
    }
    printf("\n");
}