#include <stdio.h>
#include <stdlib.h>
#include <modbus/modbus.h>
#include <errno.h>

#include "print.h"
#include "function_code_01.h" // Read coil
#include "function_code_02.h" // Read Discrete Input
#include "function_code_03.h" // Read Holding Register
#include "function_code_04.h" // Read Input Registers
#include "function_code_05.h" // Write Single Coil
#include "function_code_06.h" // Write Single Register
#include "function_code_15.h" // Write Multiple Coils
#include "function_code_16.h" // Write Multiple Holding Registers

#define server_ip "127.0.0.1"
#define server_port 50001

void run()
{
    int choice = 0;
    modbus_t *context = modbus_new_tcp(server_ip, server_port);

    if (context == NULL)
    {
        fprintf(stderr, "Failed to create Modbus context: %s\n", modbus_strerror(errno));
        modbus_close(context);
        modbus_free(context);
        exit(1);
    }

    if (modbus_connect(context) == -1)
    {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_close(context);
        modbus_free(context);
        exit(1);
    }
    print();

    scanf("%d", &choice);

    printf("\n");

    while (1)
    {
        switch (choice)
        {
        case 0x01:
            function_code_01(context);
            printf("\n");
            break;

        case 0x02:
            function_code_02(context);
            break;

        case 0x03:
            function_code_03(context);
            printf("\n");
            break;

        case 0x04:
            function_code_04(context);
            break;

        case 0x05:
            function_code_05(context);
            printf("\n");
            break;

        case 0x06:
            function_code_06(context);
            printf("\n");
            break;

        case 7:
            function_code_15(context);
            printf("\n");
            break;

        case 8:
            function_code_16(context);
            printf("\n");
            break;

        case 9:
            modbus_close(context);
            modbus_free(context);
            return;

        default:
            fprintf(stderr, "Invalid function code\n");
            break;
        }
        print();
        scanf("%d", &choice);
    }
}