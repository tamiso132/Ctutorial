#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "ecs/ecs.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"
int main(int argc, char const *argv[])
{
    EntityId *id_two = entity_add();

    free(id_two);

    // entity_generate(&id_two);
    // entity_generate(&id_two);
    // entity_generate(&id_two);

    return 0;
}