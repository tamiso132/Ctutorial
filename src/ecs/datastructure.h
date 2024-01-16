#include "ecs.h"
#include "../hashmap/hashmap.h"

typedef struct Field
{
    uint32_t archetype_id;
    uint32_t column_index;
} Field;

typedef struct Record
{
    uint32_t archtype_id;
    uint32_t row;
} Record;

typedef struct ArchtypesField
{
    /// @brief Hashmap<ArchtypeId, column_id>
    HashmapU32 archtypeid_field;
} ArchtypesField;

void *ecs_get_component(EntityId entity_id, ComponentId component);