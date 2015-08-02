#ifndef DEF_PAIR_NET
#define DEF_PAIR_NET

#include <stdlib.h>
#include <stdint.h>
#include <strings.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <tools/proto_type.h>
#include <tools/utils.h>
#include <tools/list.h>

struct Pair{
  struct sockaddr* addr;
  uint64_t time_stamp;
  uint64_t id;
};


#endif
