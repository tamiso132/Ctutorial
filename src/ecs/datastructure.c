#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "datastructure.h"
#include "../hashmap/hashmap.h"

static Vector all_archetypes;
static HashmapU64 component_map_archtypes;

#define ARCHETYPE_ARRAY_START_CAPACITY 15

void archetype_array_init()
{
    init_vector(&all_archetypes, sizeof(Archetype), ARCHETYPE_ARRAY_START_CAPACITY);
}
void archetype_add(Archetype *archtype)
{
    vector_push_element(&all_archetypes, (void *)archtype);
}

// MIGHT CHANGE SO IT IS A STRUCT WITH
// **RECORD

Record **component_get_archtypes(ComponentId id)
{
    (Vector *)hashmapU64_get(&component_map_archtypes, id.id);
}

void component_add_archetype(ComponentId id, Archetype id, ){

}
