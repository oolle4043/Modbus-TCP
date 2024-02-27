#include <modbus/modbus.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void function_code_15(modbus_t *context)
{

    int start_coil_address = 0;
    int number_of_coils = 0;
    int value = 0;

    printf("<Start coil address> <Number of coils> <Value>\n");
    scanf("%d %d %d", &start_coil_address, &number_of_coils, &value);

    if (start_coil_address < 0 || start_coil_address + number_of_coils > 2000)
    {
        printf("Exceeding the scope error\n");
        return;
    }

    if (number_of_coils == 0)
    {
        printf("Number of coils cannot be 0\n");
        return;
    }

    if (value != 0 && value != 1)
    {
        printf("Value must be 0 or 1\n");
        return;
    }

    uint8_t coil_values[number_of_coils];

    for (int i = start_coil_address; i < start_coil_address + number_of_coils; i++)
    {
        coil_values[i] = value;
    }

    // 코일 값들을 쓰기
    int rc = modbus_write_bits(context, start_coil_address, number_of_coils, coil_values);
    if (rc == -1)
    {
        fprintf(stderr, "Failed to write multiple coils: %s\n", modbus_strerror(errno));
        modbus_close(context);
        modbus_free(context);
        exit(1);
    }

    printf("Write Write Multiple Coils successful.\n");
}