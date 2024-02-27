#include <modbus/modbus.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>

#include "modbus_global.h"

void close_sigint(int dummy)
{
    if (server_socket != -1)
    {
        close(server_socket);
    }
    modbus_free(ctx);
    modbus_mapping_free(mb_mapping);

    exit(dummy);
}