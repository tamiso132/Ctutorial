#include "ecs.h"
#include "../hashmap/hashmap.h"
#include "../collection/vector.h"

typedef struct Record
{
    uint32_t archetype_id;
    uint32_t column_index;
} Record;

void archetype_add(Vector *vector, Archetype *archtype);

void hashmap_component_add(Hashmap);