#pragma once
#include <stdint.h>
#include "macro.h"

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

typedef struct MyNode // TODO, HAVE TO VALUE AFTER MyNode
{
    struct MyNode *next;
    void *value;
    uint32_t key;

} __attribute__((aligned(8))) MyNode;

typedef struct HashmapU32
{
    uint32_t current_size;
    uint32_t load_max_size;
    uint32_t max_size;
    MyNode **array;
} Hashmap;

void hashmapU32_init(Hashmap *table);

void hashmapU32_insert(Hashmap *table, uint32_t key, void *value);

void *hashmapU32_remove(Hashmap *table, uint32_t key);

void *hashmapU32_get(const Hashmap *table, uint32_t key);
