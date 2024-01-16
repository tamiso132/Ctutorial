#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "datastructure.h"
#include "../hashmap/hashmap.h"

// TODO, make safe get/set functions and make the maps inaccesable by not having my logic here

/// @brief Vector<Archtype>
static Vector all_archtypes;

/// @brief Hashmap<ComponentId, ArchtypesField>
static HashmapU64 map_component_archtypes;

/// @brief Hashmap<EntityId, Record>
static HashmapU64 map_entity_map_archtype;

void ecs_add_archtypes(ComponentId component, Field *field);
ArchtypesField *ecs_query_archtypes(ComponentId id);

Record *ecs_get_record(EntityId entity_id);
void ecs_add_archtype_field(ComponentId component, Field *field);

// should have the ArchTypeRecords owned by he hashmap
void archetype_add_new(Archetype *archtype)
{
    vector_push_element(&all_archtypes, archtype);
    // add to all components
    for (int i = 0; i < archtype->component_ids.length; i++)
    {
        Field *field = malloc(sizeof(Field));
        field->archetype_id = archtype->archetype_id;
        field->column_index = i;

        ecs_add_archtype_field(*(ComponentId *)vector_get(&archtype->component_ids, i), field);
    }

    free(archtype);
}

// MIGHT CHANGE SO IT IS A STRUCT WITH
// **RECORD

ArchtypesField *ecs_query_archtypes(ComponentId id)
{
    return (ArchtypesField *)hashmapU64_get(&map_component_archtypes, id.id);
}

// OPTIMIZATION, REMOVE BRANCHING BY CREATING THE COMPONENT ID  DURING NEW CREATION OF COMPONENT

// MIGHT HAVE THE COMPONENT HASHMAP OWN THE ARCHTYPE RECORDS
void ecs_add_archtype_field(ComponentId component, Field *field)
{
    ArchtypesField *archtypes = (ArchtypesField *)hashmapU64_get(&map_component_archtypes, component.id);

    if (archtypes == NULL)
    {

        archtypes = malloc(sizeof(ArchtypesField));

        hashmapU32_init(&archtypes->archtypeid_field);

        hashmapU64_insert(&map_component_archtypes, component.id, archtypes);
    }
    // will have to remove when I stack allocate value
    hashmapU32_insert(&archtypes->archtypeid_field, component.id, field);
}

void *ecs_get_component(EntityId entity_id, ComponentId component)
{

    ArchtypesField *field = ecs_query_archtypes(component);
    Record *record = ecs_get_record(entity_id);
    uint32_t column_index = *(uint32_t *)hashmapU32_get(&field->archtypeid_field, record->archtype_id);

    Archetype *archtype = vector_get(&all_archtypes, record->archtype_id);

    return vector_get(&archtype->columns, column_index);
}

Record *ecs_get_record(EntityId entity_id)
{
    return hashmapU64_get(&map_entity_map_archtype, entity_id.id);
}
