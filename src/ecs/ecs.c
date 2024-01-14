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

uint32_t entity_get_index(EntityId entity)
{
    return entity.id & 0xFFFF;
}
uint32_t entity_get_generation(EntityId entity)
{
    return (uint32_t)(entity.id >> 31);
}

void entity_generate(EntityId *entity)
{
    uint32_t generation = entity->id >> 31;
    generation++;

    entity->id = ((long)generation << 31) | (entity->id & 0xFFFF);

    printf("generation id: %d\n", entity_get_generation(*entity));
}
