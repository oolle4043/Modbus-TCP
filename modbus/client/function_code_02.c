#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus/modbus.h>

void function_code_02(modbus_t *context)
{
    int start_address = 0;
    int total_digital = 0;

    printf("<Start address> <Total digital>\n");
    scanf("%d %d", &start_address, &total_digital);

    if(start_address < 0 || total_digital > 2000)
    {
        printf("Exceeding the scope error\n");
        return;\
    }

    uint8_t tab_input_bits[total_digital];

    int rc = modbus_read_input_bits(context, start_address, total_digital, tab_input_bits);

    if (rc == -1)
    {
        fprintf(stderr, "Read discrete inputs failed: %s\n", modbus_strerror(errno));
        modbus_free(context);
        exit(1);
    }

    printf("Discrete inputs: ");
    for (int i = 0; i < total_digital; i++)
    {
        printf("%d ", tab_input_bits[i]);
    }
    printf("\n");
}