#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <tools/proto_type.h>
#include <tools/net_socket.h>

int main(int argc, char *argv[]){
	int socket = init_udpSocket();
	bind_udpSocket(socket,4242);
	struct netMes nm;
	while(1){
		nm = read_udpSocket(socket,NULL);

		struct sockaddr_in* si = nm.sockaddr;
	  printf("Received packet from %s:%d\n", inet_ntoa(si->sin_addr), ntohs(si->sin_port));
		char* buff = nm.data;
		printf("%i %i %s\n", nm.base->type, nm.base->len, buff);

	}
}
