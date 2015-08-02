#ifndef DEF_NET_SOCKET_TOOLS
#define DEF_NET_SOCKET_TOOLS

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

#define NET_DATA_MAX 2048
#define NET_TIMEOUT 200*TIME_MIL

struct NetMes{
  struct sockaddr* sockaddr;
  struct Base_proto* base;
  void* data;
};

struct NetBucket{
  int socket;
  struct List* wait_list;
  struct List* recv_list;
  int id_inc;
  int id_s_inc;
  int lost;
};
//sockaddr utils
struct sockaddr* get_sockaddr(char* addr,int port);

//NetMes utils
struct NetMes* gen_NetMes(struct sockaddr* sockaddr, struct Base_proto* base, void* data);
void free_NetMes(struct NetMes* nm);
int compare_id(struct NetMes* nm1, struct NetMes* nm2);
int compare_id_s(struct NetMes* nm1, struct NetMes* nm2);
int cmp_sockaddr(struct NetMes* nm1, struct NetMes* nm2);
//proto type
struct Base_proto* gen_Baseproto(uint8_t type, uint8_t flags, uint16_t len);

//base socket
int init_udpSocket();
void bind_udpSocket(int s, int port);

int write_udpSocket(int s, struct sockaddr* other,struct Base_proto* base,void* data);
struct NetMes* read_udpSocket(int s, struct sockaddr* other);

//net bucket
struct NetBucket * init_NetBucket(int s);

int write_bucket(struct NetBucket* nbucket,struct sockaddr* addr,uint8_t type, uint8_t flags, void* data, int len);
struct NetMes* read_bucket(struct NetBucket* nbucket, struct sockaddr* addr );
struct NetMes* fetch_bucket(struct NetBucket*, int id_s, struct sockaddr* addr);
int check_bucket(struct NetBucket*);

void timeout_send(struct NetBucket* nbucket,struct NetMes* nm);
struct NetMes* fetch_bucket(struct NetBucket* nbucket, int id_s, struct sockaddr* addr);
void add_ack_bucket(struct NetBucket* nbucket,struct NetMes* nm);
void add_recv_bucket(struct NetBucket* nbucket,struct NetMes* nm);

#endif
