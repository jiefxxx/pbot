#ifndef DEF_SOCKET_TOOLS
#define DEF_SOCKET_TOOLS

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define UDP		 2
#define LOCAL		 1
#define ERROR		 0

#define MAX_DATA_LEN	 2048

struct Psocket{
	int type;
	int server;
	void* sockaddr;
	int socket;
};

struct Pmessage{
	int type;
	int len;
};

struct Client{
	struct sockaddr_un client_name;
	socklen_t client_name_len;
	int client_socket_fd;
};

struct Psocket* init_Psocket(int type,int server,int port,char* addr);

#endif
