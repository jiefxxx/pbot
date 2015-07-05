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

#define NET_DATA_MAX 2048

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
//proto type
struct Base_proto* gen_Baseproto(uint8_t type, uint8_t flags, uint16_t len);

//base socket
int init_udpSocket();
void bind_udpSocket(int s, int port);

int write_udpSocket(int s, struct sockaddr* other,struct Base_proto* base,void* data);
struct netMes* read_udpSocket(int s, struct sockaddr* other);

struct sockaddr* get_sockaddr(char* addr,int port);

//net bucket
struct NetBucket * init_NetBucket(int s);

int write_bucket(struct NetBucket* nbucket,struct sockaddr* addr,uint8_t type, uint8_t flags, void* data, int len);
struct netMes* read_bucket(struct NetBucket* nbucket, struct sockaddr* addr );
struct netMes* fetch_bucket(struct netBucket*, int id_s, struct sockaddr* addr);
int check_bucket(struct netBucket*);

#endif
