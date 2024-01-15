#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "datastructure.h"

void archetype_add(Vector *vector, Archetype *archtype)
{
    vector_push_element(vector, archtype);
}
