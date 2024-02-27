#include "modbus_global.h"

#define MAX_CLIENT 5

int server_socket = -1;
modbus_t *ctx = NULL;
modbus_mapping_t *mb_mapping;
