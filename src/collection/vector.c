#include <stdlib.h>
#include <stdio.h>

#include "vector.h"
#include "assert.h"
#include "string.h"

static const int EXTRA_CAPACITY_WHEN_FULL = 50;

void init_vector(Vector *vector, const int element_size, int capacity)
{
    if (vector == NULL)
    {
        printf("fuck is happening lil bro");
    }
    vector->data = malloc(element_size * capacity);
    vector->capacity = capacity;
    vector->length = 0;
    vector->element_size = element_size;

    assert(vector->element_size > 0);
}
void vector_push_element(Vector *vector, void *element)
{
    assert(element != NULL);

    if (vector->capacity <= vector->element_size) // extend capacity
    {
        int capacity_in_bytes = vector->capacity * vector->element_size;

        int extra_space = EXTRA_CAPACITY_WHEN_FULL * vector->element_size;
        char *data = malloc(capacity_in_bytes + extra_space);
        memcpy(data, vector->data, vector->length * vector->element_size);
        free(vector->data);

        vector->data = data;
        vector->capacity += 50;

        vector_push_element(vector, element);
    }
    else // within boundaries of capacity
    {

        void *un_init_element = vector_get_unchecked(vector, vector->length);
        memcpy(un_init_element, element, vector->element_size);
        vector->length++;
    }
}
void vector_remove(Vector *vector, int index)
{
    if (index < 0 || index > vector->length)
    {
        printf("index is out of bounds");
        exit(0);
    }

    int diff_elements = vector->length - index;

    if (diff_elements > 0) //  untruncatable
    {
        int index_next_bytes = (index + 1) * vector->element_size;
        int index_bytes = vector->element_size * index;
        int bytes_to_move = diff_elements * vector->element_size;

        memmove((void *)(vector->data + index_bytes), (void *)(vector->data + index_next_bytes), bytes_to_move);
    }

    vector->length--;
}

void *vector_get_unchecked(Vector *vector, int index)
{
    int offset = vector->element_size * index;
    return vector->data + offset;
}
void *vector_get(Vector *vector, int index)
{
    if (index >= 0 && index < vector->length)
    {
        int offset = vector->element_size * index;
        return vector->data + offset;
    }
    return NULL;
}
