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
    uint32_t hash;
} Node;

uint32_t xxHash32(const void *input, size_t length, uint32_t seed);

int calculate_modulus(int value, int powerOfTwo);

KeyValuePair *create_pair(const char *key, int value, int element_size);
Node *create_node(KeyValuePair *pair, uint32_t module_number);
void destroy_node(Node *node);

int is_equal_key(const Node *one, const char *key);