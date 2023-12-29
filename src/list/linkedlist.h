#pragma once

#include "../config/config.h"

typedef struct Node Node;
typedef struct LinkedList LinkedList;

struct Node
{
    void *data;
    Node *next;
    Node *prev;
};

struct LinkedList
{
    Node *head;
    Node *tail;
};

LinkedList *list_init();

void list_push(LinkedList *list, void *data);

void *list_pop(LinkedList *list);
void *list_pop_peek(const LinkedList *list);
void *list_pop_front(LinkedList *list);
void *list_pop_front_peek(const LinkedList *list);
void list_delete_all(LinkedList *list);

void list_test();