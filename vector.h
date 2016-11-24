#ifndef _VECTOR
#define _VECTOR

#include <stdlib.h>

#define VECTOR_INITIAL_CAPACITY 4


typedef struct {
	void** items;
	size_t cap;
	size_t size;
} Vector;

void vector_new(Vector *);
int vector_size(Vector *);
void vector_add(Vector *, void *);
void vector_set(Vector *, int, void *);
void *vector_get(Vector *, int);
void vector_delete(Vector *, int);
void vector_clear(Vector *);
void vector_free(Vector *);
void vector_free_array(Vector *);

#endif
