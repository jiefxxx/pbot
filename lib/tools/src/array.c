/*struct Array* init_array(){
	struct Array* array = (struct Array*)malloc(sizeof(struct Array));
	array->count = 0;
	array->mutex = PTHREAD_MUTEX_INITIALIZER;
	return array;
}
void push_onTop(struct Array* array,void* val){
	if(array->count = 0){
		array->data = (void**)malloc(sizeof(void*)*1);
		array->data[array->count]=
		array->count++;
	}
	else if(array->count > 0){
		
	}
}
void push_onBot(struct Array* array,void* val);
void* pop_onTop(struct Array* array);
void* pop_onBot(struct Array* array);
void* pop_byId(struct Array* array, int id);*/
