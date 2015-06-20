#ifndef DEF_LIST_TOOLS
#define DEF_LIST_TOOLS

#include <stdlib.h>
#include <pthread.h>

struct List{
	struct Node_list* first;
	struct Node_list* last;
	int count;
	pthread_mutex_t mutex;
};
struct Node_list{
	void* val;
	struct Node_list* prev;
	struct Node_list* next;
};

struct List* init_list();
void* get_el(struct List* list,int id);
void push_onTop(struct List* list,void* val);
void push_onBot(struct List* list,void* val);
void* pop_onTop(struct List* list);
void* pop_onBot(struct List* list);
void* pop_byId(struct List* list, int id);


#endif
