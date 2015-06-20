#ifndef DEF_SOCKET_TOOLS
#define DEF_SOCKET_TOOLS

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

struct Client{
	struct sockaddr_un client_name;
	socklen_t client_name_len;
	int client_socket_fd;
};


#endif
