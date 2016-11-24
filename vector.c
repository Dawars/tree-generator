/*
 * vector.c
 *
 *  Created on: Nov 3, 2015
 *      Author: dawars
 */

#include "vector.h"

void vector_new(Vector *v) {
	v->cap = VECTOR_INITIAL_CAPACITY;
	v->size = 0;
	v->items = malloc(sizeof(void*) * v->cap);
}

int vector_size(Vector *v) {
	return v->size;
}

static void vector_resize(Vector *v, int new_cap) {
	void **items = realloc(v->items, sizeof(void*) * new_cap);
	if (items) {
		v->items = items;
		v->cap = new_cap;
	}

}

void vector_add(Vector *v, void *item) {
	if (v->cap == v->size)
		vector_resize(v, v->cap * 2);
	v->items[v->size++] = item;
}

void vector_set(Vector *v, int index, void *item) {
	if (index >= 0 && index < v->size)
		v->items[index] = item;
}

void *vector_get(Vector *v, int index) {
	if (index >= 0 && index < v->size)
		return v->items[index];
	return NULL;
}

void vector_delete(Vector *v, int index) {
	int i;
	if (index < 0 || index >= v->size)
		return;

	v->items[index] = NULL;

	for (i = index; i < v->size - 1; i++) {
		v->items[i] = v->items[i + 1];
		v->items[i + 1] = NULL;
	}

	v->size--;

	if (v->cap > 0 && v->cap == v->size * 4) {
		vector_resize(v, v->cap / 2);
	}
}

void vector_clear(Vector *v){
    v->size = 0;
}


void vector_free(Vector *v) {
    free(v->items);
	v->cap = 0;
	v->size = 0;
}

void vector_free_array(Vector *v) {
    int i;
    for(i = 0; i < vector_size(v); i++)
        free(vector_get(v, i));
	vector_free(v);
}
