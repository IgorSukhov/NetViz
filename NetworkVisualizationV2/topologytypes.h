#ifndef TOPOLOGYTYPES_H
#define TOPOLOGYTYPES_H

#include <stdint.h>

typedef enum {
    TYPE_FCB,
    TYPE_DOP,
    TYPE_REPE,
} board_type_t;

typedef enum {
    STATUS_OFF,
    STATUS_ON,
    STATUS_ERROR,
} port_status;

typedef enum {
    PORT_TYPE_T1S,
    PORT_TYPE_100BASE,
    PORT_TYPE_1000BASE,
} port_type;

struct board;

typedef struct {
    port_type pt;
    port_status ps;
    uint8_t userData;
    uint32_t length;
    uint8_t gunid[16u];
    board *node;
} port_param;

struct board{
    board_type_t board_type;
    uint8_t mac_addr[6u];
    uint8_t gunid[16u];
    port_param p[4u];
};

struct nodeInfo_t
{

};

#endif // TOPOLOGYTYPES_H
