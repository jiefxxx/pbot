#ifndef DEF_ARRAY_TOOLS
#define DEF_ARRAY_TOOLS

#include <stdlib.h>
#include <pthread.h>

struct Array{
	void** data;
	int count;
	pthread_mutex_t mutex;
};

/*struct Array* init_Array();
void push_onTop(struct List* list,void* val);
void push_onBot(struct List* list,void* val);
void* pop_onTop(struct List* list);
void* pop_onBot(struct List* list);
void* pop_byId(struct List* list, int id);*/


#endif
