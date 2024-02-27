#ifndef MODBUS_GLOBAL_H
#define MODBUS_GLOBAL_H

#include <modbus/modbus.h>

#define NB_CONNECTION 5

extern int server_socket;
extern modbus_t *ctx;
extern modbus_mapping_t *mb_mapping;

#endif
