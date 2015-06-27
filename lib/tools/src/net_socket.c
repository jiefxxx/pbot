#include <tools/net_socket.h>

struct sockaddr* get_sockaddr(char* addr,int port){
  struct sockaddr_in* si = malloc(sizeof(struct sockaddr_in));
  if(addr == NULL){
    si->sin_family = AF_INET;
  	si->sin_port = htons(port);
  	si->sin_addr.s_addr = htonl(INADDR_ANY);
  }
  else{
    si->sin_family = AF_INET;
  	si->sin_port = htons(port);
  	si->sin_addr.s_addr = inet_addr(addr);
  }

  return (struct sockaddr*)si;
}

int init_udpSocket(){

	int s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //initialisation du socket udp

	if(s == -1) die("ERROR||init_udpSocket():",-1);

	return s;
}

void bind_udpSocket(int s, int port){

  struct sockaddr* si = get_sockaddr(NULL,port);

	if( bind(s, si, sizeof(struct sockaddr))==-1){
		die("ERROR||bind_udpSocket(int port)",-1);
	}

  free(si);
}

int write_udpSocket(int s, struct sockaddr* other,struct Base_proto* base,void* data){

  if(base->len>NET_DATA_MAX){
    return -1;
  }

  int len = sizeof(struct Base_proto)+base->len;
  int ret;

  void* mes = malloc(len);

  memcpy(mes,base,sizeof(struct Base_proto));
  memcpy(mes+sizeof(struct Base_proto),data,base->len);


  ret = sendto(s,mes,len,0,other,sizeof(struct sockaddr));

  free(mes);
  return ret;
}

struct netMes read_udpSocket(int s, struct sockaddr* other){

  struct netMes nm;

  int len_malloc = sizeof(struct Base_proto)+NET_DATA_MAX;
  socklen_t len_sockaddr =  sizeof(struct sockaddr);

  if(other == NULL){
    other = malloc(sizeof(struct sockaddr_in));
    bzero(other,sizeof(struct sockaddr_in));
  }
  void* mess = (void*)malloc(len_malloc);

  bzero(mess,len_malloc);

  if(recvfrom(s, mess, len_malloc, 0, other , &len_sockaddr) == -1){

    free(other);
    free(mess);

    nm.base = NULL;
    nm.sockaddr = NULL;
    nm.data = NULL;

    return nm;
  }

  nm.base = mess;
  nm.base = realloc(mess,nm.base->len+sizeof(struct Base_proto));
  mess = nm.base;
  nm.sockaddr = other;
  nm.data = mess+sizeof(struct Base_proto);

  return nm;

}

void free_netMes(struct netMes nm){
  free(nm.sockaddr);
  free(nm.base);
  free(nm.data);
}
