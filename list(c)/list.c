
#include "list.h"
#include <stdlib.h>

typedef struct Node {
	void* data;
	struct Node* next;
} Node;

typedef struct List {
	Node* head;
	size_t count_el;
	size_t itemSize;
}List;

void* slist_create(size_t itemSize) {
	if (itemSize == 0) {
		return NULL;
	}
	List* slist = calloc(1, sizeof(List));
	if (slist == NULL){
		return NULL;
	}
	slist->itemSize = itemSize;
	return slist;
}

void* create_node(List* list) {
	Node* new_node = calloc(1, sizeof(Node));
	if (new_node == NULL) {
		return NULL;
	}
	new_node->data = calloc(1, list->itemSize);
	if (new_node->data == NULL) {
		return NULL;
	}
	return new_node;
}

void* slist_prepend(void* slist) {
	if (slist == NULL) {
		return NULL;
	}
	List* list = (List*)slist;
	Node* new = create_node(list);
	new->next = list->head;
	list->head = new;
	list->count_el += 1;
	return list->head->data;
}

size_t slist_count(const void* slist) {
	if (slist == NULL) {
		return INVALID;
	}
	List* list = (List*)slist;
	return list->count_el;
}

void slist_destroy(void* slist, void(destroy)(void*)) {
	slist_clear(slist, destroy);
	free(slist);
}

void slist_clear(void* slist, void(*destroy)(void*)) {
	if (slist == NULL) {
		return;
	}
	List* list = (List*)slist;
	while (list->count_el != 0) {
		slist_remove(slist, destroy);
	}
}

void slist_remove(void* slist, void(*destroy)(void*)) {
	if (slist == NULL) {
		return;
	}
	List* list = (List*)slist;
	if (list->head == NULL) {
		return;
	}
	Node* deleted_node = list->head;
	list->head = list->head->next;
	if (destroy) {
		destroy(deleted_node->data);
	}
	free(deleted_node->data);
	free(deleted_node);
	list->count_el--;
}

void* slist_item(void* slist, size_t i) {
	if (slist == NULL) {
		return NULL;
	}
	List* list = (List*)slist;
	if (list->head == NULL) {
		return NULL;
	}
	if (i >= list->count_el) {
		return NULL;
	}
	Node* desired_node = list->head;
	for (size_t count = 0; count < i; count++) {
		desired_node = desired_node->next;
	}
	if (desired_node->data) {
		return desired_node->data;
	}
	return NULL;
}

void* slist_init(void* slist, size_t itemSize, void(*destroy)(void*)) {
	if (slist == NULL || itemSize == 0) {
		return NULL;
	}
	List* list = (List*)slist;
	slist_clear(slist, destroy);
	list->itemSize = itemSize;
	return list;
}

size_t slist_first(const void* slist) {
	if (slist == NULL) {
		return INVALID;
	}
	List* list = (List*)slist;
	if (list->head) {
		return (size_t)(list->head);
	}
	else {
		return slist_stop(slist);
	}
}

size_t slist_next(const void* slist, size_t item_id) {
	if (slist == NULL || item_id == slist_stop(slist)) {
		return slist_stop(slist);
	}
	Node* current = (Node*)item_id;
	if (current == NULL || current->next == NULL) {
		return slist_stop(slist);
	}
	return (size_t)(current->next);
}

size_t slist_stop(const void* slist) {
	if (slist == NULL) {
		return INVALID;
	}
	return (size_t)(INVALID-1);
}

void* slist_current(const void* slist, size_t item_id) {
	if (slist == NULL) {
		return NULL;
	}
	List* list = (List*)slist;
	if (list->head == NULL || item_id == slist_stop(list)) {
		return NULL;
	}
	Node* current = (Node*)item_id;
	return current->data;
}

void* slist_insert(void* slist, size_t item_id) {
	if (slist == NULL) {
		return NULL;
	}
	List* list = (List*)slist;
	if (item_id == slist_stop(list) && list->count_el == 0) {
		return slist_prepend(slist);
	}
	if (item_id == slist_stop(slist)) {
		return NULL;
	}
	Node* current = (Node*)item_id;
	if (current == NULL) {
		return NULL;
	}
	Node* new = create_node(list);
	new->next = current->next;
	current->next = new;
	list->count_el++;
	return new->data;
}

void slist_erase(void* slist, size_t item_id, void(*destroy)(void*)) {
	if (slist == NULL) {
		return;
	}
	List* list = (List*)slist;
	if (list->count_el == 0 || item_id == slist_stop(slist)) {
		return;
	}
	Node* previous = list->head;
	if ((size_t)(previous) == item_id) {
		slist_remove(slist, destroy);
		return;
	}
	while ((size_t)(previous->next) != item_id) {
		previous = previous->next;
		if (previous->next == NULL) {
			return;
		}
	}
	Node* current = (Node*)item_id;
	previous->next = current->next;
	if (destroy) {
		destroy(current->data);
	}
	free(current->data);
	free(current);
	list->count_el--;
}