#include <stdlib.h>
#include <sys/socket.h>
#include <modbus/modbus.h>
#include <unistd.h>

#include "global_variables.h"

static void close_sigint(int dummy)
{
    if (server_socket != -1)
    {
        close(server_socket);
    }
    modbus_free(ctx);
    modbus_mapping_free(mb_mapping);

    exit(dummy);
}