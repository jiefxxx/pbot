int NetBucket_write(struct NetBucket* nbucket,struct NetMes* nmes){

  NetMes_set_id(nmes,NetBucket_get_new_id(nbucket));
  NetMes_set_id_r(nmes,NetBucket_get_new_track_id(nbucket));
  NetMes_set_base_timestamp(nmes);
  write_udpSocket(NetBucket_get_net_socket(nbucket),nmes);
  NetBucket_add_new_mes(nbucket,nmes);
  return NetMes_get_id_r(nmes);
}

void NetBucket_write_again(struct NetBucket* nbucket,struct NetMes* nmes){

  NetMes_set_id(nmes,NetBucket_get_new_id(nbucket));
  NetMes_set_base_timestamp(nmes);
  write_udpSocket(NetBucket_get_net_socket(nbucket),nmes);
}

struct NetMes* NetBucket_read(struct NetBucket* nbucket, struct Pair* pair){

  struct NetMes* nmes;
  struct sockaddr* addr;
  if(pair == NULL){
    addr = NULL;
  }
  else{
    addr = Pair_get_addr(pair);
  }
  while(1){
    nmes = read_udpSocket(NetBucket_get_net_socket(nbucket),addr);
    if(NetMes_is_valid(nmes)){
      NetMes_set_pair(nmes,NetBucket_set_pairs(nbucket,NetMes_get_pair(nmes)));
      if(!NetBucket_update_new_mes(nmes)){
        return nmes;
      }
    }
  }
}

int NetBucket_check(struct NetBucket* nbucket){
  int ret;
  struct List* list = NetBucket_add_wait_mes(nbucket);
  lock_list(list);
  struct Node_list* tmp = get_first_node(list);
  struct NetMes* nm;
  while(is_valid_node(tmp)){
    nm = get_node_val(tmp);
    if(NetMes_check_timeout(nm,NETBUCKET_TIMEOUT*TIME_MIL)){
      NetBucket_write_again(nbucket,nm);
      ret++;
    }
    else{
      tmp = get_next_node(tmp);
    }
  }
  unlock_list(list);
  return ret;
}

struct NetMes* NetBucket_get_recev(struct NetBucket* nbucket,int id_r){
  int ret;
  struct List* list = NetBucket_add_recev_mes(nbucket);
  lock_list(list);
  struct Node_list* tmp = get_first_node(list);
  struct NetMes* nm;
  while(is_valid_node(tmp)){
    nm = get_node_val(tmp);
    if(NetMes_check_id_r(nm,id_r)){
      if(NetMes_get_state(nm) == RECEV_COMPLET){
        del_node(tmp);
      }
      else{
        unlock_list(list);
        NetMes_lock(nm);
        NetMes_wait_recev(nm);
        NetMes_unlock(nm);
        lock_list(list);
        del_node(tmp);
      }
      unlock_list(list);
      return nm;
    }
    else{
      tmp = get_next_node(tmp);
    }
  }
  unlock_list(list);
  return NULL;
}

struct NetMes* NetBucket_ask(struct NetBucket* nbucket,struct NetMes* nmes){
  NetMes_free_flags(nmes,ACK|RCV);
  NetMes_add_flags(nmes,REQUEST_ACK|REQUEST_RCV);
  return NetBucket_get_recev(nbucket,NetBucket_write(nbucket,nmes));
}

int NetBucket_secure_send(struct NetBucket* nbucket,struct NetMes* nmes){
  NetMes_free_flags(nmes,ACK|RCV);
  NetMes_add_flags(nmes,REQUEST_ACK);
  return NetBucket_write(nbucket,nmes);
}

void NetBucket_quick_send(struct NetBucket* nbucket,struct NetMes* nmes){
  NetMes_set_flags(nmes,0X0);
  NetBucket_write(nbucket,nmes);
}

void NetBucket_reply(struct NetBucket nbucket,struct NetMes* nmes){
  NetMes_free_flags(nmes,REQUEST_RCV);
  NetMes_add_flags(nmes,RCV|REQUEST_ACK);
  NetBucket_write_again(nbucket,nmes);
  NetBucket_add_new_mes(nbucket,nmes);
}
