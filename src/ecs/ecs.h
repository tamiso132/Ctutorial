#include <stdint.h>
#include <stdio.h>

#define MAX_SIZE 1000
// Sparse Set Data Structure
struct SparseSet
{
    int sparse[MAX_SIZE]; // Sparse array
    int dense[MAX_SIZE];  // Dense array
    int size;             // Number of elements in the set
};

typedef struct EntityId
{
    uint64_t id;
} EntityId;

EntityId entity_add();

void entity_generate(EntityId entity);
uint64_t entity_get_generation(EntityId entity);
uint64_t entity_get_index(EntityId entity);

// Function to initialize a sparse array