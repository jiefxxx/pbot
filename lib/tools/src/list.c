#include<tools/list.h>
struct List* init_list(){
	struct List* head = (struct List*)malloc(sizeof(struct List));
	head->first = NULL;
	head->last = NULL;
	head->count = 0;
	pthread_mutex_init(&head->mutex, NULL);
	return head;
}
void* get_el(struct List* list,int id){
	int i;
	struct Node_list* tmp;
	pthread_mutex_lock(&list->mutex);
	tmp = list->first;
	for(i=0;i<id;i++){
		if(tmp->next == NULL){
			pthread_mutex_unlock(&list->mutex);
			return NULL;
		}
		tmp = tmp->next;
	}
	pthread_mutex_unlock(&list->mutex);
	return tmp->val;
}
void push_onTop(struct List* list,void* el){
	struct Node_list* newNode = (struct Node_list*)malloc(sizeof(struct Node_list));
	newNode->val = el;
	newNode->prev = NULL;
	pthread_mutex_lock(&list->mutex);
	newNode->next = list->first;
	if (list->first != NULL){
		list->first->prev=newNode;
	}
	list->first=newNode;
	if(list->last == NULL){
		list->last=newNode;
	}
	list->count++;
	pthread_mutex_unlock(&list->mutex);
}
void push_onBot(struct List* list,void* el){
	struct Node_list* newNode = (struct Node_list*)malloc(sizeof(struct Node_list));
	newNode->val = el;
	newNode->next = NULL;
	pthread_mutex_lock(&list->mutex);
	newNode->prev = list->last;
	if(list->last != NULL){
		list->last->next=newNode;
	}
	list->last=newNode;
	if(list->first == NULL){
		list->first = newNode;
	}
	list->count++;
	pthread_mutex_unlock(&list->mutex);
}
void* pop_onTop(struct List* list){
	pthread_mutex_lock(&list->mutex);
	if(list->first == NULL){
		pthread_mutex_unlock(&list->mutex);
		return NULL;
	}
	struct Node_list* tmpNode = list->first;
	void* tmpVal = tmpNode->val;
	list->first = tmpNode->next;
	if (list->first != NULL){
		list->first->prev=NULL;
	}
	list->count--;
	pthread_mutex_unlock(&list->mutex);
	free(tmpNode);
	return tmpVal;
}
void* pop_onBot(struct List* list){
	pthread_mutex_lock(&list->mutex);
	if(list->last == NULL){
		pthread_mutex_unlock(&list->mutex);
		return NULL;
	}
	struct Node_list* tmpNode = list->last;
	void* tmpVal = tmpNode->val;
	list->last = tmpNode->prev;
	if (list->last != NULL){
		list->last->next=NULL;
	}
	list->count--;
	pthread_mutex_unlock(&list->mutex);
	free(tmpNode);
	return tmpVal;
}
void* pop_byId(struct List* list, int id){
	int i;
	struct Node_list* tmp;
	void* tmp_val;
	pthread_mutex_lock(&list->mutex);
	tmp = list->first;
	for(i=0;i<(id-1);i++){
		if(tmp->next == NULL){
			pthread_mutex_unlock(&list->mutex);
			return NULL;
		}
		tmp = tmp->next;
	}
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
	pthread_mutex_unlock(&list->mutex);
	tmp_val = tmp->val;
	free(tmp);
	return tmp_val;
}
