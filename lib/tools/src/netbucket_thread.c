void NetBucket_starting_thread(struct NetBucket* nbucket,void (*handler)(struct NetBucket*,struct NetMes*)){
  nbucket->handler = handler;
  pthread_create(&nbucket->recev_thread,NULL,NetBucket_recev_thread,(void*)nbucket);
  pthread_create(&nbucket->check_thread,NULL,NetBucket_check_thread,(void*)nbucket);
}

void NetBucket_check_thread(struct NetBucket* nbucket){
  while(1){
    sleep(200*TIME_MIL);
    NetBucket_check(nbucket);
  }
}

void NetBucket_recev_thread(struct NetBucket* nbucket){
  struct NetMes* nmes;
  while(1){
    nmes = NetBucket_read(nbucket,NULL);
    (*nbucket->handler)(nbucket,nmes);
  }
}
