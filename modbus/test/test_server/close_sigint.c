#include <modbus/modbus.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>

static int server_socket = -1;
static modbus_t *ctx = NULL;
static modbus_mapping_t *mb_mapping;

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