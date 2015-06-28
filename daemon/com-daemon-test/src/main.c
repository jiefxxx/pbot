#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <tools/proto_type.h>
#include <tools/net_socket.h>

int main(int argc, char *argv[]){
	int socket = init_udpSocket();
	struct sockaddr* o = get_sockaddr("127.0.0.1",4242);
	struct Base_proto bp;
	bp.type = 1;
	bp.len = 10;
	bp.flag = 0;
	bp.id = 0;
	while(1){
		if(write_udpSocket(socket,o,&bp,"blablabla")==-1) {
			break;
		};
	}
}
