
#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "allocator/alloc.h"
#include "collection/linkedlist.h"
#include "collection/vector.h"
#include "hashmap/hashmap.h"

void benchmark_operations()
{
    Hashmap table;
    hashmap_init(&table);
    hashmap_destroy(&table);
}

#pragma GCC diagnostic ignored "-Wunused-parameter" // for disable main parameter warning
int main(int argc, char const *argv[])
{

    benchmark_operations();
    return 0;
}
#pragma GCC diagnostic warning "-Wunused-parameter"
