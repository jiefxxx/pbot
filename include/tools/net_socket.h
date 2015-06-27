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

struct netMes{
  struct sockaddr* sockaddr;
  struct Base_proto* base;
  void* data;
};

int init_udpSocket();
void bind_udpSocket(int s, int port);

int write_udpSocket(int s, struct sockaddr* other,struct Base_proto* base,void* data);
struct netMes read_udpSocket(int s, struct sockaddr* other);

struct sockaddr* get_sockaddr(char* addr,int port);

#endif
