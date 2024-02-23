#include "global_variables.h"

static modbus_t *ctx = NULL;
static int server_socket = -1;
static modbus_mapping_t *mb_mapping;
