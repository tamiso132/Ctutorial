#pragma once
typedef struct Vector Vector;
struct Vector
{
    int element_size;
    int length;
    int capacity;
    char *data;
};

void init_vector(Vector *vector, const int element_size, int capacity);

void vector_push_element(Vector *vector, void *element);

void vector_remove(Vector *vector, int index);

void *vector_get(Vector *vector, int index);

void *vector_get_unchecked(Vector *vector, int index);