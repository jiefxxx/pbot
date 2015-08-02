
struct NetBucket* NetBucket_init(){
  struct NetBucket* nbucket = (struct NetBucket*)malloc(sizeof(struct NetBucket));
  bzero(nbucket,sizeof(struct NetBucket));
  nbucket->pairs = List_init();
  nbucket->wait_Mes = List_init();
  nbucket->recv_Mes = List_init();
  return nbucket;
}

void NetBucket_free(void* nbucket){
  List_free(nbucket->pairs,Pair_free);
  List_free(nbucket->wait_mes,NetMes_free);
  List_free(nbucket->recev_mes,NetMes_free);
  free(nbucket);
}
//accessor
int NetBucket_get_new_id(struct NetBucket* nbucket){
  nbucket->id_inc++;
  return id_inc;
}

int NetBucket_get_new_track_id(struct NetBucket* nbucket){
  nbucket->id_track_inc++;
  return id_track_inc;
}

int NetBucket_get_net_socket(struct NetBucket* nbucket){
  return nbucket->net_socket;
}

int NetBucket_get_cast_socket(struct NetBucket* nbucket){
  return nbucket->cast_socket;
}

struct List* NetBucket_get_pairs(struct NetBucket* nbucket){
  return nbucket->pairs;
}
struct List* NetBucket_get_wait_mes(struct NetBucket* nbucket){
  return nbucket->wait_mes;
}
struct List* NetBucket_get_recv_mes(struct NetBucket* nbucket){
  return nbucket->recv_mes;
}
//editor
void NetBucket_set_net_socket(struct NetBucket* nbucket,int socket){
  nbucket->net_socket = socket;
}

void NetBucket_set_cast_socket(struct NetBucket* nbucket,int socket){
  nbucket->cast_socket = socket;
}

struct Pair* NetBucket_set_pairs(struct NetBucket* nbucket,struct Pair* pair){
  struct List* list = NetBucket_get_pairs(nbucket);
  lock_list(list);
  struct Node_list* tmp = get_first_node(list);
  while(is_valid_node(tmp)){
    if(Pair_comp(get_node_val(tmp),pair)){
      Pair_free(pair);
      pair = get_node_val(tmp);
      unlock_list(list);
      return pair;
    }
    else{
      tmp = get_next_node(tmp);
    }
  }
  unlock_list(list);
  push_onTop(list,pair);
  return pair;
}

void NetBucket_add_wait_mes(struct NetBucket nbucket,struct NetMes* nmes){

  struct List* list = NetBucket_get_wait_mes(nbucket);
  push_onTop(list,nmes);
}

void NetBucket_add_recev_mes(struct NetBucket nbucket,struct NetMes* nmes){
  struct List* list = NetBucket_get_recev_mes(nbucket);
  struct NetMes* nmes_r = NetMes_make();
  NetMes_set_state(nmes_r,WAITING);
  NetMes_set_pair(nmes_r,NetMes_get_pair(nmes));
  NetMes_set_id_r(nmes_r,NetMes_get_id_r(nmes));
  NetMes_set_type(nmes_r,NetMes_get_type(nmes));
  NetMes_set_action(nmes_r,NetMes_get_action(nmes));
  push_onTop(list,nmes_r);
}

void NetBucket_add_new_mes(struct NetBucket nbucket, struct NetMes* nmes){
  if(NetMes_is_valid(nmes)){
    NetMes_set_state(nmes,WAITING);
    if(NetMes_check_flags(REQUEST_ACK)){
      NetBucket_add_wait_mes(nbucket,nmes);
    }
    if(NetMes_check_flags(REQUEST_RCV)){
      NetBucket_add_recev_mes(nbucket,nmes);
    }
  }
  NetMes_free(nmes);
}

void NetBucket_update_wait_mes(struct NetBucket* nbucket,struct NetMes* nmes){
  struct List* list = NetBucket_get_wait_mes(nbucket);
  lock_list(list);
  struct Node_list* tmp = get_first_node(list);
  struct NetMes* nm;
  while(is_valid_node(tmp)){
    nm = get_node_val(tmp)
    if(NetMes_comp_ack(nm,nmes)){

      NetMes_free(nm);
      NetMes_free(nmes);
      del_node(list,tmp);
      unlock_list(list);
      return;
    }
    else{
      tmp = get_next_node(tmp);
    }
  }
  unlock_list(list);
}

void NetBucket_update_recev_mes(struct NetBucket* nbucket,struct NetMes* nmes){
  struct List* list = NetBucket_get_recev_mes(nbucket);
  lock_list(list);
  struct Node_list* tmp = get_first_node(list);
  struct NetMes* nm;
  while(is_valid_node(tmp)){
    nm = get_node_val(tmp);
    if(NetMes_comp(nm,nmes)){
      NetMes_lock(nm);
      NetMes_set_state(tmp,RECEV_COMPLET);
      NetMes_set_data(tmp,NetMes_get_data(nmes),NetMes_get_data_len(nmes));
      NetMes_broadcast_recev(nm);
      NetMes_unlock(nm);
      free(nmes);
      unlock_list(list);
      return;
    }
    else{
      tmp = get_next_node(tmp);
    }
  }
  unlock_list(list);
}

int NetBucket_update_new_mes(struct NetBucket nbucket,struct NetMes* nmes){
  if(NetMes_is_valid(nmes)){
    if(NetMes_check_flags(ACK)){
      NetBucket_update_wait_mes(nbucket,nmes);
      return 1;
    }
    if(NetMes_check_flags(RCV)){
      NetBucket_udpate_recev_mes(nbucket,nmes);
      return 1;
    }
    return 0;
  }
  free_netMes(nmes);
  return 1;
}


//makor
