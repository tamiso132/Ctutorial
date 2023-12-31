#pragma once
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>

typedef struct KeyValuePair
{
    char *key;
    int value;
} KeyValuePair;

typedef struct Node
{
    KeyValuePair pair;
    struct Node *next;
} Node;

uint32_t xxHash32(const void *input, size_t length, uint32_t seed);

KeyValuePair *create_pair(const char *key, int value, int element_size);
Node *create_node(KeyValuePair *pair);
void destroy_node(Node *node);

int is_equal_key(const Node *one, const char *key);