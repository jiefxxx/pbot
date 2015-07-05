compare #include<tools/list.h>
struct List* init_list(){
	struct List* head = (struct List*)malloc(sizeof(struct List));
	head->first = NULL;
	head->last = NULL;
	head->count = 0;
	pthread_mutex_init(&head->mutex, NULL);
	return head;
}
void* get_byID(struct List* list,int id){
	int i = 0;
	struct Node_list* tmp;

	lock_list(list);
	tmp = get_first_node(list);
	while(is_valid_node(tmp)){
		if(i == id){
			unlock_list(list);
			return get_node_val(tmp);
		}
		else{
			i++;
			tmp = get_next_node(tmp);
		}
	}
	unlock_list(list);
	return NULL;
}

void push_onTop(struct List* list,void* el){
	struct Node_list* newNode = make_node(el);
	lock_list(list);
	add_node_top(list,newNode,NULL);
	unlock_list(list);
}

void push_onBot(struct List* list,void* el){
	struct Node_list* newNode = make_node(el);
	lock_list(list);
	add_node_bot(list,newNode,NULL);
	unlock_list(list);
}

void* pop_onTop(struct List* list){
		lock_list(list);
		struct Node_list* tmp = get_last_node(list);
		if(is_valid_node(tmp)){
			del_node(list,tmp);
			unlock_list(list);
			return free_node(tmp);
		}
		unlock_list(list);
		return NULL;
}

void* pop_onBot(struct List* list){
	lock_list(list);
	struct Node_list* tmp = get_last_node(list);
	if(is_valid_node(tmp)){
		del_node(list,tmp);
		unlock_list(list);
		return free_node(tmp);
	}
	unlock_list(list);
	return NULL;
}

void* pop_byId(struct List* list, int id){
	int i = 0;
	struct Node_list* tmp;

	lock_list(list);
	tmp = get_first_node(list);
	while(is_valid_node(tmp)){
		if(i == id){
			del_node(list,tmp);
			unlock_list(list);
			return free_node(tmp);
		}
		else{
			i++;
			tmp = get_next_node(tmp);
		}
	}
	unlock_list(list);
	return NULL;
}

int is_valid_node(struct Node_list* tmp){
	if(tmp == NULL){
		return 0;
	}
	return 1;
}

int is_first_node(struct Node_list* tmp){
	if(tmp->prev == NULL){
		return 1;
	}
	return 0;
}

int is_last_node(struct Node_list* tmp){
	if(tmp->next == NULL){
		return 1;
	}
	return 0;
}

void lock_list(struct List* list){
	pthread_mutex_lock(&list->mutex);
}

void unlock_list(struct List* list){
	pthread_mutex_unlock(&list->mutex);
}

struct Node_list* get_first_node(struct List* list){
	return list->first;
}

struct Node_list* get_last_node(struct List* list){
	return tmp->next;
}

struct Node_list* get_prev_node(struct Node_list* tmp){
	return tmp->prev;
}

struct Node_list* get_next_node(struct Node_list* tmp){
	return tmp->next;
}

void* get_node_val(struct Node_list* tmp){
	return tmp->val;
}

struct Node_list* make_node(void* el){
	struct Node_list* newNode = (struct Node_list*)malloc(sizeof(struct Node_list));
	newNode->val = el;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

void* free_node(struct Node_list* tmp){
	void* ret = get_node_val(tmp);
	free(tmp);
	return ret;
}

void add_node_top(struct List* list, struct Node_list* newNode, struct Node_list* next){
	if(next == NULL){
		newNode->next = list->first;
		if (list->first != NULL){
			list->first->prev=newNode;
		}
		list->first=newNode;
		if(list->last == NULL){
			list->last=newNode;
		}
	}
	else{
		newNode->next = next;
		if(next->prev == NULL){
			list->first = newNode;
			newNode->prev = NULL;
		}
		else{
			newNode->prev = next->prev;
		}
		next->prev=newNode;
	}
	list->count++;
}

void add_node_bot(struct List* list, struct Node_list* newNode, struct Node_list* prev){
	if(prev == NULL){
		newNode->prev = list->last;
		if(list->last != NULL){
			list->last->next=newNode;
		}
		list->last=newNode;
		if(list->first == NULL){
			list->first = newNode;
		}
	}
	else{
		newNode->prev = prev;
		if(prev->next == NULL){
			list->last = newNode;
			newNode->next = NULL;
		}
		else{
			newNode->next = prev->next;
		}
		prev->next=newNode;
	}
	list->count++;
}

void del_node(struct List* list,struct Node_list* tmp){
	if(tmp->prev == NULL){
		if(tmp->next == NULL){
			list->first=NULL;
			list->last=NULL;
		}
		else{
			list->first=tmp->next;
			list->first->prev=NULL;
		}
	}
	else{
		if(tmp->next == NULL){
			list->last=tmp->prev;
			list->last->next=NULL;
		}
		else{
			tmp->prev->next=tmp->next;
			tmp->next->prev=tmp->prev;
		}
	}
	list->count--;
}
