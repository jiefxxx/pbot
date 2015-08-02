#ifndef DEF_PROTO_TOOLS
#define DEF_PROTO_TOOLS

#include <stdint.h>

#define REQUEST_ACK 0x1
#define REQUEST_RCV 0x2
#define ACK 0x4
#define RCV 0x8

struct Base_proto{
  uint8_t type;
  uint8_t flags;
  uint16_t len;
  uint16_t id;
  uint16_t id_s;
  uint64_t time_stamp;
};

#endif
