#ifndef DEF_BUCKET_TOOLS
#define DEF_BUCKET_TOOLS

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

struct NetBucket{
  int net_socket;
  int cast_socket;

  struct List* pairs;
  struct List* wait_mes;
  struct List* recv_mes;

  int id_inc;
  int id_track_inc;
  int lost;

  void (*handler)(struct NetBucket*,struct NetMes*);

  pthread_t recev_thread;
  pthread_t check_thread;
  
};

#define NETBUCKET_TIMEOUT 200;

struct NetBucket* NetBucket_init();
void NetBucket_free(void* nbucket);

int NetBucket_get_new_id(struct NetBucket* nbucket);
int NetBucket_get_new_track_id(struct NetBucket* nbucket);

int NetBucket_get_net_socket(struct NetBucket* nbucket);
int NetBucket_get_cast_socket(struct NetBucket* nbucket);

struct List* NetBucket_get_pairs(struct NetBucket* nbucket);
struct List* NetBucket_get_wait_mes(struct NetBucket* nbucket);
struct List* NetBucket_get_recv_mes(struct NetBucket* nbucket);

void NetBucket_set_net_socket(struct NetBucket* nbucket,int socket);
void NetBucket_set_cast_socket(struct NetBucket* nbucket,int socket);
struct Pair* NetBucket_set_pairs(struct NetBucket* nbucket,struct Pair* pair);

void NetBucket_add_wait_mes(struct NetBucket nbucket,struct NetMes* nmes);
void NetBucket_add_recev_mes(struct NetBucket nbucket,struct NetMes* nmes);
void NetBucket_add_new_mes(struct NetBucket nbucket, struct NetMes* nmes);

void NetBucket_update_wait_mes(struct NetBucket* nbucket,struct NetMes* nmes);
void NetBucket_update_recev_mes(struct NetBucket* nbucket,struct NetMes* nmes);
int NetBucket_update_new_mes(struct NetBucket nbucket,struct NetMes* nmes);


#endif
