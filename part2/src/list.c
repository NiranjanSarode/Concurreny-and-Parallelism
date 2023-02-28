#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"


void list_rm(struct list* l, struct listentry* e){    
	if(e->prev == NULL && e->next == NULL){
		l->head = NULL;
		l->tail = NULL;
	}
	else if(e->prev == NULL){
		e->next->prev = NULL;
		l->head = e->next;
	}
	else if(e->next == NULL){
		e->prev->next = NULL;
		l->tail = e->prev;
	}
	else{
		e->prev->next = e->next; 
		e->next->prev = e->prev;
	}
	//free(e);
}

struct listentry* list_add(struct list* l, void* data){  
	struct listentry* new_entry = (struct listentry*)malloc(sizeof(struct listentry));
	if(l->head == NULL){
		new_entry->data = data;
		new_entry->prev = l->tail;
		new_entry->next = NULL;
		l->head = new_entry;
		l->tail = new_entry;
	}
	else{
		new_entry->data = data;
		new_entry->prev = l->tail;
		new_entry->next = NULL;
		l->tail->next = new_entry;
		l->tail = new_entry;
	}
	return new_entry;
}

struct list* list_new(){  
	struct list* l = (struct list*)malloc(sizeof(struct list));
    l->head = NULL;
    l->tail = NULL;
    return l;
}

int is_empty(struct list* l){  
	return l->head == NULL;
}
