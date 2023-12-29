#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

void add(LinkedList list, void *data)
{
    Node *node = calloc(1, sizeof(Node));
    node->data = data;

    if (list.head == NULL)
    {
        list.head = node;
        list.tail = node;
    }
    else
    {
        node->next = NULL;
        node->prev = list.tail;

        list.tail = node;
    }
}

void *list_pop(LinkedList *list)
{
    if (list->tail != NULL)
    {
        void *pop = list->tail->data;
        list->tail = list->tail->prev;
        return pop;
    }
    return NULL;
}
void *list_pop_peek(const LinkedList *list)
{
    if (list->tail == NULL)
    {
        return NULL;
    }
    return list->tail->data;
}