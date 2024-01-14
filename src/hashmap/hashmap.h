#pragma once
#include <stdint.h>

typedef struct MyNode
{
    struct MyNode *next;
    uint32_t value;
    uint32_t key;
} __attribute__((aligned(8))) MyNode;
typedef struct Hashmap
{
    uint32_t current_size;
    uint32_t load_max_size;
    uint32_t max_size;
    MyNode **array;
} Hashmap;

void hashmap_init(Hashmap *table);

Hashmap *hashmap_heap_init();

void hashmap_insert(Hashmap *table, uint32_t key, uint32_t value);

void hashmap_remove(Hashmap *table, uint32_t key);

uint32_t hashmap_get(const Hashmap *table, uint32_t key);

void hashmap_destroy(Hashmap *table);