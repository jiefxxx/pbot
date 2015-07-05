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
//high level
void* get_byID(struct List* list,int id);
void push_onTop(struct List* list,void* val);
void push_onBot(struct List* list,void* val);
void* pop_onTop(struct List* list);
void* pop_onBot(struct List* list);
void* pop_byId(struct List* list, int id);
//low level
int is_valid_node(struct Node_list* tmp);
int is_first_node(struct Node_list* tmp);
int is_last_node(struct Node_list* tmp);
void lock_list(struct List* list);
void unlock_list(struct List* list);
struct Node_list* get_first_node(struct List* list);
struct Node_list* get_last_node(struct List* list);
struct Node_list* get_prev_node(struct Node_list* tmp);
struct Node_list* get_next_node(struct Node_list* tmp);
void* get_node_val(struct Node_list* tmp);
struct Node_list* make_node(void* el);
void* free_node(struct Node_list* tmp);
void add_node_top(struct List* list, struct Node_list* newNode, struct Node_list* next);
void add_node_bot(struct List* list, struct Node_list* newNode, struct Node_list* prev);
void del_node(struct List* list,struct Node_list* tmp);

#endif
