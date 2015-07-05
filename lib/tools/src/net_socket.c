#include <tools/net_socket.h>
#include <tools/time.h>

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

struct netMes* read_udpSocket(int s, struct sockaddr* other){

  struct netMes* nm = (struct netMes*)malloc(sizeof(struct netMes));

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
    free(nm);
    nm = NULL;
    return nm;
  }

  nm->base = mess;
  nm->base = realloc(mess,nm->base->len+sizeof(struct Base_proto));
  mess = nm->base;
  nm->sockaddr = other;
  nm->data = mess+sizeof(struct Base_proto);

  return nm;

}
struct NetMes* gen_netMes(struct sockaddr* sockaddr,struct Base_proto* base, void* data){
  struct NetMes* nm = (struct NetMes*)malloc(sizeof(struct NetMes));
  nm->sockaddr = sockaddr;
  nm->base = base;
  nm->data = data;
  return nm;
}

void free_netMes(struct netMes* nm){
  free(nm->sockaddr);
  free(nm->base);
  free(nm->data);
  free(nm);
}

struct Base_proto* gen_Baseproto(uint8_t type, uint8_t flags, uint16_t len){
  struct Base_proto* proto = (struct proto_type*)malloc(sizeof(struct proto_type));
  proto->type = type;
  proto->flags = flags;
  proto->len = len;
  proto->time_stamp = timeStamp();
}

struct NetBucket* init_NetBucket(int s){
  struct NetBucket* nbucket = (struct NetBucket*)malloc(sizeof(struct NetBucket));
  bzero(nbucket,sizeof(struct NetBucket));
  nbucket->socket = s;
  nbucket->wait_list = init_list();
  nbucket->recv_list = init_list();
  return nbucket;
}

int write_bucket(struct NetBucket* nbucket,struct sockaddr* addr,uint8_t type, uint8_t flags, void* data, int len){
  struct Base_proto* base = gen_Baseproto(type,flags,len);

  nbucket->id_inc++;
  nbucket->id_s_inc++;
  base->id = id_inc;
  base->id_s = id_s_inc;

  write_udpSocket(nbucket->socket,addr,base,data);

  if ((base->flags & REQUEST_ACK) == REQUEST_ACK){
    push_onBot(nbucket->wait_list,gen_netMes(addr,base,data));
  }

  if ((base->flags & REQUEST_RCV) == REQUEST_RCV){
    struct Base_proto* base_r = gen_Baseproto(0,0x0,0);
    base_r->id_s = id_s_inc;
    push_onBot(nbucket->recv_list,gen_netMes(addr,base_r,NULL));
  }

  return id_s_inc;
}

struct NetMes* read_bucket(struct NetBucket* nbucket, struct sockaddr* addr ){
  struct NetMes* nm;
  while(true){
    nm = read_udpSocket(nbucket->socket,addr);
    if ((nm->base->flags & REQUEST_ACK) == REQUEST_ACK){
      send_ack_bucket(nbucket,nm->base,nm->sockaddr);
    }
    if ((nm->base->flags & ACK) == ACK){
      add_ack_bucket(nbucket,nm);
      free_netMes(nm);
    }
    else if ((nm->base->flags & RCV) == RCV){
      add_recv_bucket(nbucket,nm);
    }
    else{
      return nm;
    }
  }
}

struct netMes* fetch_bucket(struct netBucket*, int id_s, struct sockaddr* addr);
int check_bucket(struct netBucket*);

void add_ack_bucket(struct netBucket nbucket,struct netMes* nm){
  lock_list(nbucket->wait_list);
  struct Node_list* tmp = get_first_node(nbucket->wait_list);
  while(is_valid_node(tmp)){
    if(cmp_sockaddr((struct netMes*)get_node_val(tmp),nm)
              && cmp_id((struct netMes*)get_node_val(tmp),nm)){
      del_node(nbucket->wait_list,tmp);
      free_netMes((struct netMes*)free_node(tmp));
      unlock_list(nbucket->wait_list);
      return;
    }
    else{
      tmp = get_next_node(tmp);
    }
  }
  unlock_list(nbucket->wait_list);
  return;
}

void add_recv_bucket(struct netBucket nbucket,struct netMes* nm){
  lock_list(nbucket->wait_list);
  struct Node_list* tmp = get_first_node(nbucket->wait_list);
  while(is_valid_node(tmp)){
    if(cmp_sockaddr((struct netMes*)get_node_val(tmp),nm)
              && cmp_id_s((struct netMes*)get_node_val(tmp),nm)){
      del_node(nbucket->wait_list,tmp);
      free_netMes((struct netMes*)free_node(tmp));
      add_node_bot(nbucket->wait_list,make_node(nm),NULL);
      unlock_list(nbucket->wait_list);
      return;
    }
    else{
      tmp = get_next_node(tmp);
    }
  }
  unlock_list(nbucket->wait_list);
  return;
}

int cmp_sockaddr(struct netMes* nm1, struct netMes* nm2){
  struct sockaddr_in *in1 = (void*)nm1->sockaddr, *in2 = (void*)nm2->sockaddr;
  if(ntohl(in1->sin_addr.s_addr) != ntohl(in2->sin_addr.s_addr)){
    return 0;
  }
  if(ntohl(in1->sin_port) != ntohl(in2->sin_port)){
    return 0;
  }
  return 1;
}

int compare_id(struct netMes* nm1, struct netMes* nm2){
  if(nm1->base->id != nm2->base->id){
    return 0;
  }
  return 1;
}

int compare_id_s(struct netMes* nm1, struct netMes* nm2){
  if(nm1->base->id_s != nm2->base->id_s){
    return 0;
  }
  return 1;
}
