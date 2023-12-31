#pragma once
// Include necessary headers
#include <stddef.h> // for size_t
#include <stdint.h>
#include <stdlib.h> // for malloc, free
#include <string.h> // for strdup, strlen

// Forward declarations
typedef struct HashTable HashTable;

// public method
void hashmap_insert(HashTable **table, const char *key, int value);
int hashmap_remove(HashTable *table, const char *key);
int hashmap_get(const HashTable *table, const char *key);

void hashmap_init(HashTable **table, size_t max_size, size_t element_size);
void hashmap_destroy(HashTable *table);
