#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "linkedlist.h"

#define TRUE 1
#define FALSE 0

void list_init(LinkedList **listt)
{
    (*listt) = calloc(1, sizeof(LinkedList));
}

void list_delete_all(LinkedList **listt)
{
    LinkedList *list = *listt;
    while (list->tail != NULL)
    {
        free(list_pop(list));
    }
    free(*listt);
    *listt = NULL;
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
        if (list->tail != NULL)
        {
            list->tail->next = NULL;
        }
        else
        {
            list->head = NULL;
            list->tail = NULL;
        }
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
    if (list->head != NULL)
    {
        Node *pop_front_node = list->head;
        void *data = pop_front_node->data;
        list->head = list->head->next;
        free(pop_front_node);

        if (list->head == NULL)
        {
            list->tail = NULL;
        }
        return data;
    }
    return NULL;
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

/**
 * @brief Inserts behind the node behind the indexed node
 * @return return 1 for success.
 */
int list_insert(LinkedList *list, int index, void *data)
{
    int current_index = 0;
    Node *current = list->head;
    while (current != NULL)
    {
        if (index == current_index)
        {
            // setup for new node
            Node *insert = malloc(sizeof(Node));
            insert->data = data;
            insert->next = current;
            insert->prev = current->prev;

            // put new node behind current
            current->prev = insert;

            if (current_index > 0) // if there is a behind orginally
            {
                // put node behind currents next to the new behind.
                current->prev->next = insert;
            }
            else
            {
                list->head = insert;
            }
            return TRUE;
        }
    }
    if (current_index == 0) // no values in and insert at 0
    {
        Node *first_value = malloc(sizeof(Node));
        first_value->data = data;
        first_value->next = NULL;
        first_value->prev = NULL;

        list->head = first_value;
        list->tail = first_value;
        return TRUE;
    }
    return FALSE;
}
