#pragma once
#include <stdint.h>
#include "macro.h"

DEFINE_HASHMAP_HEADER(HashmapU32, uint32_t, uint32_t)

typedef struct SetU64Node
{
    struct SetU64Node *next;
    uint64_t key;
} SetU64Node;
typedef struct SetU64
{
    uint64_t max_size;
    SetU64Node **array;
    uint64_t current_size;
    uint64_t load_max_size;
} SetU64;
void SetU64_init(SetU64 *table);
void SetU64_insert(SetU64 *table, uint64_t key);
void SetU64_destroy(SetU64 *table);
void SetU64_remove(SetU64 *table, uint64_t key);
uint64_t *SetU64_get(const SetU64 *table, uint64_t key);

DEFINE_HASHMAP_HEADER(HashmapSet, uint64_t, SetU64)
// typedef struct MyNode
// {
//     struct MyNode *next;
//     uint32_t value;
//     uint32_t key;
// } __attribute__((aligned(8))) MyNode;
// typedef struct Hashmap
// {
//     uint32_t current_size;
//     uint32_t load_max_size;
//     uint32_t max_size;
//     MyNode **array;
// } Hashmap;

// void hashmap_init(Hashmap *table);

// Hashmap *hashmap_heap_init();

// void hashmap_insert(Hashmap *table, uint32_t key, uint32_t value);

// void hashmap_remove(Hashmap *table, uint32_t key);

// uint32_t hashmap_get(const Hashmap *table, uint32_t key);

// void hashmap_destroy(Hashmap *table);
