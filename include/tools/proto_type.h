#ifndef DEF_PROTO_TOOLS
#define DEF_PROTO_TOOLS

#include <stdint.h>

struct Base_proto{
  uint8_t type;
  uint8_t flag;
  uint16_t len;
  uint16_t id;
};

#endif
