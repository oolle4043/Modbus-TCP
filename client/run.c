#include <stdio.h>
#include <stdlib.h>

#include "function_code_01.h"
#include "function_code_03.h"

void run(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage:%s <ip> <port> <function_code>\n", argv[0]);
        exit(1);
    }

    switch (atoi(argv[3]))
    {
    case 0x01:
        function_code_01(argv);
        break;
    case 0x03:
        function_code_03(argv);
        break;
    default:
        fprintf(stderr, "Invalid function code\n");
        break;
    }
}