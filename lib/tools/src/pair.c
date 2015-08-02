#include <net/pair.h>

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


struct Pair* Pair_make(struct sockaddr* addr){
  struct Pair* pair = malloc(sizeof(struct Pair));
  bzero(pair,sizeof(struct Pair));
  pair->addr = addr
  return pair;
}

struct Pair* Pair_make_manual(char* addr,int port){
  return Pair_make(get_sockaddr(addr,port));
}


void Pair_free(struct Pair* pair){
  free(pair->addr);
  free(pair);
}

void Pair_update_timestamp(struct Pair* pair){
  pair->time_stamp = timeStamp();
}

struct sockaddr* Pair_get_addr(struct Pair* pair){
  return pair->addr;
}

struct sockaddr* Pair_get_id(struct Pair* pair){
  return pair->id;
}

void Pair_set_id(struct Pair* pair, uint64_t id){
  pair->id = id;
}

int Pair_comp(struct Pair* p1, struct Pair* p2){
  struct sockaddr_in *in1 = p1->addr, *in2 = p2->addr;
  if(ntohl(in1->sin_addr.s_addr) != ntohl(in2->sin_addr.s_addr)){
    return 0;
  }
  if(ntohl(in1->sin_port) != ntohl(in2->sin_port)){
    return 0;
  }
  return 1;
}

int Pair_check_time_stamp(struct Pair* pair,uint64_t timeout){
  if((pair->time_stamp+timeout) < timeStamp()){
    return 1;
  }
  return 0;
}
