#include<tools/socket.h>

int connect_server(char* socket_path,int clients){
	struct sockaddr_un name;
	int socket_fd = socket(PF_LOCAL,SOCK_STREAM,0);
	name.sun_family = AF_LOCAL;
	strcpy(name.sun_path, socket_path);
	if(bind(socket_fd, &name, SUN_LEN(&name))<0){
		return -1;
	}
	else{
		listen (socket_fd,clients);
		return socket;
	}
}

void* accept_clients_thread(void* _thread){
	struct Thread* thread = (struct Thread*)_thread;
	struct List* list = (struct List*)thread->data;
	struct Client* client;
	do {
		client = (struct Client*)malloc(sizeof(struct Client))
		client->client_socket_fd=accept (socket_fd, &client_name, &client_name_len);
		/* Handle the connection. */
		client_sent_quit_message = server (client_socket_fd);
		/* Close our end of the connection. */
		close (client_socket_fd);
	}

int connect_client(char* socket_path){
	struct sockaddr_un name;
	int socket_fd = socket(PF_LOCAL,SOCK_STREAM,0);
	name.sun_family = AF_LOCAL;
	strcpy(name.sun_path, socket_path);
	if(connect(socket_fd, &name, SUN_LEN(&name))<0){
		return -1;
	}
	else{
		return socket;
	}
}


