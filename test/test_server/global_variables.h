#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include <modbus/modbus.h>

static modbus_t *ctx = NULL;
extern int server_socket;
extern modbus_mapping_t *mb_mapping;

#endif
