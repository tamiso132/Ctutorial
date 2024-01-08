// #pragma once

// #include <assert.h>
// #include <stddef.h> // for size_t
// #include <stdint.h>
// #include <stdlib.h> // for malloc, free
// #include <string.h> // for strdup, strlen

// typedef struct HashTable HashTable;

// void hashmap_insert(HashTable **table, const char *key, int value);
// int hashmap_remove(HashTable *table, const char *key);
// int hashmap_get(const HashTable *table, const char *key);
// void hashmap_init(HashTable **table, uint32_t max_size, size_t element_size);
// void hashmap_destroy(HashTable *table);

// // for benchmarking
// uint32_t xxHash32(const void *input, size_t length, uint32_t seed);