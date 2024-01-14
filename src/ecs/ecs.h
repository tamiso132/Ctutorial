#pragma once
#include <stdint.h>
#include <stdio.h>
#include "xxhash.h"
#include "../hashmap/hashmap.h"
#define MAX_SIZE 1000
// works by having indexes that map to all
// non zero values in the dense array

typedef struct EntityId
{
    uint64_t id;
} EntityId;

typedef struct Archetype
{
    char *start;
    uint32_t amount;
    Hashmap entities_map;
};

struct SparseSet
{
    int sparse[MAX_SIZE]; // Sparse array
    int dense[MAX_SIZE];  // Dense array
    int size;             // Number of elements in the set
};

EntityId entity_add();

void entity_generate(EntityId *entity);
uint32_t entity_get_generation(EntityId entity);
uint32_t entity_get_index(EntityId entity);

// Function to initialize a sparse array