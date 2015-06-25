#ifndef DEF_THREAD_TOOLS
#define DEF_THREAD_TOOLS

#include <stdlib.h>
#include <pthread.h>

struct Thread{
	void* data;
	int state;
	pthread_t thread;
	pthread_mutex_t mutex;
};
struct Thread* start_thread(void*(*routine)(void *),void* data);

#endif
