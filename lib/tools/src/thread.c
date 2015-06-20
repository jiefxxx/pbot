#include<tools/thread.h>

struct Thread* start_thread(void*(*sroutine)(void *),void* data){
	struct Thread* thread = (struct Thread*)malloc(sizeof(struct Thread));
	thread->data = data;
	thread->state = 0;
	pthread_mutex_init(&thread->mutex, NULL);
	if(pthread_create(&thread->thread,NULL,routine,(void*)thread)<0){
		free(thread);
		return NULL;
	}
	else{
		return thread;
	}
}

void* join_thread(struct Thread* thread){
	void* thread_return;
	pthread_join (thread,*thread_return);
	free(thread);
	return thread_return;
}
