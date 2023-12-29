#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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
    printf("\nhello");
    list = NULL;
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

    printf("wtf");
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
    printf("wtf");
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

        if (list->head == NULL)
        {
            list->tail = NULL;
        }
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

void list_test()
{
    printf("list test start\n");
    // Create a new linked list
    LinkedList *list = list_init();

    // Test list_push
    int data1 = 42;
    list_push(list, &data1);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(list->head->data == &data1);
    assert(list->tail->data == &data1);

    printf("list test start\n");

    // Test list_pop
    void *pop_data = list_pop(list);
    assert(pop_data == &data1);
    assert(list->head == NULL);
    assert(list->tail == NULL);

    printf("list test start\n");
    // Test list_push again
    int data2 = 55;
    list_push(list, &data2);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(list->head->data == &data2);
    assert(list->tail->data == &data2);

    printf("list test start\n");

    // Test list_pop_front
    void *pop_front_data = list_pop_front(list);
    assert(pop_front_data == &data2);
    assert(list->head == NULL);
    assert(list->tail == NULL);

    printf("list test start\n");
    // Test other functions as needed

    // Clean up
    list_delete_all(list);

    assert(list == NULL);
    printf("list test done\n");
}