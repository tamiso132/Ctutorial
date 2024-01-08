#include <stdint.h>

#include "ecs.h"

uint16_t current_index;

EntityId entity_add()
{
    EntityId id;
    id.id = current_index;
    current_index += 1;

    return id;
}

uint64_t entity_get_index(EntityId entity)
{
    return entity.id & 0xFFFF;
}
uint64_t entity_get_generation(EntityId entity)
{
    return (uint32_t)(entity.id >> 32);
}

void entity_generate(EntityId entity)
{
    entity.id = entity.id & 0xFFFF | (((entity.id << 31) & 0xFFFF) + 1) << 31;
}
