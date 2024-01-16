#pragma once
#include <stdint.h>
#include <stdio.h>
#include "xxhash.h"

#include "../collection/vector.h"
#include "../hashmap/hashmap.h"
#define MAX_SIZE 1000
// works by having indexes that map to all
// non zero values in the dense array

typedef struct Column
{
    void *elements;
    size_t element_size;
} Column;

typedef struct EntityId
{
    uint64_t id;
} EntityId;

typedef struct ComponentId
{
    uint64_t id;
} ComponentId;
/// @brief all enities with unique combination of components
typedef struct Archetype
{
    uint64_t archetype_id;
    /// @brief entity id mapped to index in archtype
    // HashmapU32 entity_map;
    uint32_t max_size;
    /// @brief every column has it own component data
    Vector columns;

    Vector component_ids;
} Archetype;

struct SparseSet
{
    int sparse[MAX_SIZE]; // Sparse array
    int dense[MAX_SIZE];  // Dense array
    int size;             // Number of elements in the set
};

EntityId *entity_add();

void entity_generate(EntityId *entity);
uint32_t entity_get_generation(EntityId entity);
uint32_t entity_get_index(EntityId entity);

// Function to initialize a sparse array
