struct NetMes* NetMes_make(){
  struct NetMes* nmes = malloc(sizeof(struct NetMes));
  bzero(nmes,sizeof(struct NetMes));
  nmes->pair = NULL;
  nmes->data = NULL;
  nmes->time_stamp = timeStamp();
  pthread_mutex_init(&nmes->mutex, NULL);
  pthread_cond_init(&nmes->cond_ack, NULL);
  pthread_cond_init(&nmes->cond_recev, NULL);
  return nmes;
}

void NetMes_free(struct NetMes* nmes){
  free(nmes->data);
  free(nmes);
}

void NetMes_lock(struct NetMes* nmes){
  pthread_mutex_lock(&nmes->mutex);
}

void NetMes_unlock(struct NetMes* nmes){
  pthread_mutex_unlock(&nmes->mutex);
}

void NetMes_wait_ack(struct NetMes* nmes){
  pthread_cond_wait(&nmes->cond_ack,&nmes->mutex);
}

void NetMes_wait_recev(struct NetMes* nmes){
  pthread_cond_wait(&nmes->cond_recev,&nmes->mutex);
}

void NetMes_broadcast_ack(struct NetMes* nmes){
  pthread_cond_broadcast(&nmes->cond_ack);
}

void NetMes_broadcast_recev(struct NetMes* nmes){
  pthread_cond_broadcast(&nmes->cond_recev);
}

int NetMes_is_valid(struct NetMes* nmes){
  if(nmes->state == 0) return 0;
  if(nmes->pair == NULL) return 0;
  //if(nmes->data == NULL) return 0;
  return 1;
}

void NetMes_set_pair(struct NetMes* nmes,struct Pair* pair){
  nmes->pair = pair;
}

void NetMes_set_data(struct NetMes* nmes, int len, void* data){
  if(nmes->data != NULL){
    free(nmes->data);
    nmes->data = NULL;
  }
  if(len > NET_DATA_MAX){
    return;
  }
  nmes->data = data;
  nmes->base.len = len;
}

void NetMes_set_type(struct NetMes* nmes,int type, int action){
  nmes->type = type;
  nmes->action = action;
}

void NetMes_set_flags(struct NetMes* nmes, uint8_t flags){
  nmes->flags = flags;
}

void NetMes_add_flags(struct NetMes* nmes, uint8_t flags){
  nmes->flags = nmes->flags|flags;
}

void NetMes_free_flags(struct NetMes* nmes, uint8_t flags){
  nmes->flags = nmes->flags&~flags;
}

void NetMes_set_id(struct NetMes* nmes, int id){
  nmes->id = id;
}

void NetMes_set_id_r(struct NetMes* nmes, int id_r){
  nmes->id_r = id_r;
}

void NetMes_set_base_timestamp(struct NetMes* nmes){
  nmes->base->time_stamp = time_stamp();
}

void NetMes_set_state(struct NetMes* nmes,int state){
  nmes->state = state;
}

struct Pair* NetMes_get_pair(struct NetMes* nmes){
  return nmes->pair;
}

void* NetMes_get_data(struct NetMes* nmes){
  return nmes->data;
}

int NetMes_get_data_len(struct NetMes* nmes){
  return nmes->len;
}

int NetMes_get_type(struct NetMes* nmes){
  return nmes->base.type;
}

int NetMes_get_action(struct NetMes* nmes){
  return nmes->base.action;
}

int NetMes_get_id(struct NetMes* nmes){
  return nmes->base.id;
}

int NetMes_get_id_r(struct NetMes* nmes){
  return nmes->base.id_r;
}

int NetMes_get_base_timestamp(struct NetMes* nmes){
  return nmes->base.time_stamp;
}

int NetMes_get_timestamp(struct NetMes* nmes){
  return nmes->time_stamp;
}

int NetMes_check_flags(struct NetMes* nmes,flag){
  if ((base->flags & flag) == flag){
    return 1;
  }
  return 0;
}

int NetMes_check_pair(struct NetMes* nmes, struct Pair* pair){
  return Pair_comp(nmes->pair,pair);
}

int NetMes_check_id(struct NetMes nmes, int id){
  if(nmes->base.id == id){
    return 1;
  }
  return 0;
}

int NetMes_check_id_r(struct NetMes nmes, int id_r){
  if(nmes->base.id_r == id_r){
    return 1;
  }
  return 0;
}

int NetMes_check_timeout(struct NetMes nmes, int timeout){
  if((nmes->time_stamp+timeout)<timeStamp()){
    return 1;
  }
  return 0;
}

int NetMes_check_ack_timeout(struct NetMes nmes, int timeout){
  if((nmes->base.time_stamp+timeout)<timeStamp()){
    return 1;
  }
  return 0;
}

int NetMes_cmp(struct NetMes* nmes1, struct NetMes* nmes2){
  if(nmes1->base.id_r != nmes2->base.id_r){
    return 0;
  }
  if(nmes1->base.type != nmes2->base.type){
    return 0;
  }
  if(nmes1->base.action != nmes2->base.action){
    return 0;
  }
  if(!Pair_comp(nmes1->pair,nmes2->pair)){
    return 0;
  }
  return 1;
}

int NetMes_cmp_ack(struct NetMes* nmes1, struct NetMes* nmes2){
  if(nmes1->base.id != nmes2->base.id){
    return 0;
  }
  if(nmes1->base.type != nmes2->base.type){
    return 0;
  }
  if(nmes1->base.action != nmes2->base.action){
    return 0;
  }
  if(!Pair_comp(nmes1->pair,nmes2->pair)){
    return 0;
  }
  return 1;
}

int NetMes_get_compil_len(struct NetMes* nmes){
  return sizeof(struct BaseProt)+NetMes_get_data_len(nmes);
}

void* NetMes_compil(struct NetMes* nmes){
  void* data = malloc(NetMes_get_compil_len(nmes));
  memcpy(data,&nmes->base,sizeof(struct BaseProto));
  memcpy(data+sizeof(struct BaseProt),nmes->data,nmes->base.len);
  return data;
}

void NetMes_decompil(struct NetMes* nmes,void* mes){

  memcpy(mes,&nmes->base,sizeof(struct BaseProt));
  nmes->data = malloc(sizeof(nmes->base.len));
  memcpy(mes+sizeof(struct BaseProt),nmes->data,nmes->base.len);
}

struct sockaddr* NetMes_get_sockaddr(struct NetMes* nmes){
  return Pair_get_addr(nmes->pair);
}
