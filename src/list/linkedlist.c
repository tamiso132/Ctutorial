#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

LinkedList *list_init()
{
    LinkedList *list = malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void list_delete_all(LinkedList *list)
{
    while (list->tail != NULL)
    {
        Node *node_to_delete = list->tail;
        list->tail = list->tail->prev;
        free(node_to_delete);
    }
    free(list);
}

void list_push(LinkedList *list, void *data)
{
    Node *node = calloc(1, sizeof(Node));
    node->data = data;

    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        node->next = NULL;
        node->prev = list->tail;

        list->tail->next = node;
        list->tail = node;
    }
}

void *list_pop(LinkedList *list)
{
    if (list->tail != NULL)
    {
        Node *pop_node = list->tail;
        void *data = pop_node->data;

        list->tail = list->tail->prev;
        list->tail->next = NULL;

        free(pop_node);
        return data;
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
void *list_pop_front(LinkedList *list)
{
    if (list->tail != NULL)
    {
        Node *pop_front_node = list->head;
        void *data = pop_front_node->data;
        list->head = list->head->next;
        free(pop_front_node);
        return data;
    }
}

void *list_pop_front_peek(const LinkedList *list)
{
    if (list->head == NULL)
    {
        return NULL;
    }
    else
    {
        return list->head->data;
    }
}