#ifndef DEF_PROTO_TOOLS
#define DEF_PROTO_TOOLS

#include <stdint.h>

struct Base_proto{
  uint8_t type;
  uint8_t flags;
  uint16_t len;
  uint16_t id;
  uint16_t id_s;
  uint64_t time_stamp;
};

#endif
