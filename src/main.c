#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "ecs/ecs.h"
#include "xxhash.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"
int main(int argc, char const *argv[])
{
    EntityId *id_two = entity_add();

    free(id_two);
    XXH64_hash_t t = XXH64("hello", 6, 0);
    // entity_generate(&id_two);
    // entity_generate(&id_two);
    // entity_generate(&id_two);

    return 0;
}