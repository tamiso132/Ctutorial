#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#include "ecs/ecs.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"
int main(int argc, char const *argv[])
{
    EntityId id = entity_add();
    EntityId id_two = entity_add();

    entity_generate(id_two);
    entity_generate(id_two);

    printf("id: %ld\n", entity_get_generation(id_two));
    printf("id: %ld\n", entity_get_index(id_two));
    return 0;
}
