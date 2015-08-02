#include <tools/net_socket.h>
#include <tools/time.h>

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

int write_udpSocket(int s, struct NetMes* nmes){


  int len = NetMes_get_compil_len(nmes);
  void* mes = NetMes_compil(nmes);
  struct sockaddr* addr = NetMes_get_sockaddr(nmes);
  int ret;

  ret = sendto(s,mes,len,0,other,sizeof(struct sockaddr));

  free(mes);
  return ret;
}

struct NetMes* read_udpSocket(int s, struct sockaddr* other){

  if(other == NULL){
    other = malloc(sizeof(struct sockaddr_in));
    bzero(other,sizeof(struct sockaddr_in));
  }

  socklen_t len_sockaddr =  sizeof(struct sockaddr);
  int len_malloc = sizeof(struct BaseProt)+NET_DATA_MAX;
  void* mess = (void*)malloc(len_malloc);
  bzero(mess,len_malloc);

  if(recvfrom(s, mess, len_malloc, 0, other , &len_sockaddr) == -1){

    free(other);
    free(mess);
    return NULL;
  }

  struct NetMes* nmes = NetMes_make();

  NetMes_decompil(mess);
  NetMes_set_sockaddr(other);

  free(mess);
  return nmes;

}















void timeout_send(struct NetBucket* nbucket,struct NetMes* nm){
    nbucket->id_inc++;
    struct sockaddr* addr = nm->sockaddr;
    struct Base_proto* base = nm->base;
    base->id = nbucket->id_inc;
    base->time_stamp = timeStamp();
    void* data = nm->data;
    write_udpSocket(nbucket->socket,addr,base,data);
    return;
}

void send_ack_bucket(struct NetBucket* nbucket,struct Base_proto* base,struct sockaddr* addr){
  struct Base_proto* base_s = gen_Baseproto(base->type,ACK,0);

}

struct NetMes* fetch_bucket(struct NetBucket* nbucket,
                              int id_s, struct sockaddr* addr){
  return NULL;
  }

int check_bucket(struct NetBucket* nbucket){
  int i = 0;
  lock_list(nbucket->wait_list);
  struct Node_list* tmp = get_first_node(nbucket->wait_list);
  struct NetMes* nm;
  while(is_valid_node(tmp)){
    nm = (struct NetMes*)get_node_val(tmp);
    if(nm->base->time_stamp > (timeStamp()+NET_TIMEOUT)){
      i++;
      timeout_send(nbucket,nm);
    }
    tmp = get_next_node(tmp);
  }
  unlock_list(nbucket->wait_list);
  return i;
}

void add_ack_bucket(struct NetBucket* nbucket,struct NetMes* nm){
  lock_list(nbucket->wait_list);
  struct Node_list* tmp = get_first_node(nbucket->wait_list);
  while(is_valid_node(tmp)){
    if(cmp_sockaddr((struct NetMes*)get_node_val(tmp),nm)
              && cmp_id((struct NetMes*)get_node_val(tmp),nm)){
      del_node(nbucket->wait_list,tmp);
      free_NetMes((struct NetMes*)free_node(tmp));
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

void add_recv_bucket(struct NetBucket* nbucket,struct NetMes* nm){
  lock_list(nbucket->wait_list);
  struct Node_list* tmp = get_first_node(nbucket->wait_list);
  while(is_valid_node(tmp)){
    if(cmp_sockaddr((struct NetMes*)get_node_val(tmp),nm)
              && cmp_id_s((struct NetMes*)get_node_val(tmp),nm)){
      del_node(nbucket->wait_list,tmp);
      free_NetMes((struct NetMes*)free_node(tmp));
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
