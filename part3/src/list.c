/**
 * @brief Linked list implementation
 * Linked list implementation for the part 3 of the project.
 */
#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"

/**
 * @brief Removes an element from the list
 * Set the attributes of the previous and next element of the element to be removed
 * @param[in] l struct list* l -> the linked list whose element is to be removed
 * @param[in] e struct listentry* e -> the element to be removed
 * @return void 
 */
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

/**
 * @brief Adds an element to the list
 * @param[in] l struct list* l -> the linked list to which the element is to be added
 * @param[in] data void* data -> the data to be added to the list
 * @return struct listentry* new_entry -> the new entry added to the list
 */
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

/**
 * @brief Creates a empty list
 * @return struct list* l -> the new list created
 */
struct list* list_new(){  
	struct list* l = (struct list*)malloc(sizeof(struct list));
    l->head = NULL;
    l->tail = NULL;
    return l;
}

/**
 * @brief Checks if the list is empty
 * @param[in] l struct list* l -> the linked list to be checked
 * @return int 1/true if empty else 0/false
 */
int is_empty(struct list* l){  
	return l->head == NULL;
}
