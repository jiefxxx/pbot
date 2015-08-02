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

#define REQUEST_ACK 0x1
#define REQUEST_RCV 0x2
#define ACK 0x4
#define RCV 0x8

struct BaseProt{
  uint16_t type;
  uint8_t action;
  uint8_t flags;
  uint16_t len;
  uint16_t id;
  uint16_t id_r;
  uint64_t time_stamp;
};


struct NetMes{
  int state;
  struct Pair* pair;
  struct BaseProt base;
  uint64_t time_stamp;
  void* data;
  pthread_mutex_t mutex;
  pthread_cond_t cond_ack;
  pthread_cond_t cond_recev;
};

struct NetMes* NetMes_make();
void NetMes_free(struct NetMes* nmes);
int NetMes_is_valid(struct NetMes* nmes);

void NetMes_set_pair(struct NetMes* nmes,struct Pair* pair);
void NetMes_set_data(struct NetMes* nmes, int len, void* data);
void NetMes_set_type(struct NetMes* nmes,int type, int action);
void NetMes_set_flags(struct NetMes* nmes, uint8_t flags);
void NetMes_set_id(struct NetMes* nmes, int id);
void NetMes_set_id_r(struct NetMes* nmes, int id_r);
void NetMes_set_base_timestamp(struct NetMes* nmes);
void NetMes_set_state(struct NetMes* nmes,int state);

struct Pair* NetMes_get_pair(struct NetMes* nmes);
void* NetMes_get_data(struct NetMes* nmes);


#endif
