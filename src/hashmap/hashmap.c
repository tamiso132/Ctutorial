// #include <stdio.h>
// #include "hashmap.h"

// static const float EXTEND_LOAD_FACTOR = 0.7;
// #define GET_FAILED INT32_MAX - 1

// typedef struct KeyValuePair
// {
//     char *key;
//     int value;
// } KeyValuePair;

// typedef struct Node
// {
//     KeyValuePair *pair;
//     struct Node *next;
// } Node;

// struct HashTable
// {
//     size_t element_size;
//     size_t max_size_power_of_two;
//     size_t current_size;
//     size_t max_size_allowed;
//     Node **array;
// };

// void destroy_node(Node *node);

// void hashmap_resize(HashTable **tablee, size_t new_size);
// size_t get_max_size(HashTable *table);

// ////////////////////////////////////////////////////////////////////////////////
// //// HELPER FUNCTIONS
// ////////////////////////////////////////////////////////////////////////////////
// uint32_t xxHash32(const void *input, size_t length, uint32_t seed);

// size_t calculate_modulus(int value, size_t powerOfTwo);

// int is_equal_key(const Node *one, const char *key);

// uint32_t XXH32_rotl(uint32_t x, int r);

// uint32_t XXH32_round(uint32_t acc, uint32_t input);

// uint32_t XXH32_mergeAccs(uint32_t acc1, uint32_t acc2, uint32_t acc3, uint32_t acc4);

// uint32_t XXH_read32(const void *memPtr);

// // Function to insert a key-value pair into the hash table
// void hashmap_insert(HashTable **table, const char *key, int value)
// {
//     assert(key != NULL);
//     assert(*table != NULL);
//     HashTable *table_deref = *table;

//     int n_index = xxHash32(key, strlen(key), 0);

//     size_t index = calculate_modulus(n_index, table_deref->max_size_power_of_two); // FIX THIS LATER

//     KeyValuePair *pair = malloc(sizeof(KeyValuePair));
//     pair.key = malloc(strlen(key) + 1);

//     //  KeyValuePair pair;
//     // pair.key = malloc(strlen(key) + 1);
//     // pair.value = value;

//     // strcpy(pair.key, key);

//     Node *new_node = malloc(sizeof(Node));
//     new_node->next = NULL;
//     new_node->pair = pair;

//     new_node->next = table_deref->array[index];
//     table_deref->array[index] = new_node;

//     table_deref->current_size++;
//     if (table_deref->current_size > table_deref->max_size_allowed)
//     {
//         hashmap_resize(table, table_deref->max_size_power_of_two);
//     }
// }

// int hashmap_remove(HashTable *table, const char *key) // dont shrink during remove, do it during get
// {
//     size_t hash_index = calculate_modulus(xxHash32(key, strlen(key), 0), table->max_size_power_of_two);

//     if (table->array[hash_index] != NULL)
//     {
//         Node *node = table->array[hash_index];
//         Node *prev = table->array[hash_index];

//         assert(&node->pair != NULL);

//         if (is_equal_key(node, key))
//         {
//             Node *temp = table->array[hash_index];
//             table->array[hash_index] = node->next;
//             table->current_size--;
//             destroy_node(temp);
//             return 1;
//         }

//         prev = node;
//         node = node->next;

//         while (node != NULL)
//         {
//             assert(&node->pair != NULL);

//             if (is_equal_key(node, key))
//             {
//                 prev->next = node->next;
//                 destroy_node(node);
//                 table->current_size--;
//                 return 1;
//             }
//             prev = node;
//             node = node->next;
//         }
//     }
//     return -1;
// }

// // return -1 if not found
// int hashmap_get(const HashTable *table, const char *key)
// {
//     assert(key != NULL);
//     size_t index = calculate_modulus(xxHash32(key, strlen(key), 0), table->max_size_power_of_two);

//     // Traverse the linked list to find the key
//     Node *current = table->array[index];
//     while (current != NULL)
//     {
//         if (is_equal_key(current, key))
//         {
//             return current->pair.value;
//         }
//         current = current->next;
//     }

//     // Key not found
//     printf("should not happen\n");
//     return GET_FAILED;
// }

// // Function to create a new hash table
// void hashmap_init(HashTable **tablee, uint32_t power_of_two, size_t element_size)
// {
//     *tablee = malloc(sizeof(HashTable));
//     HashTable *table_deref = *tablee;

//     table_deref->max_size_power_of_two = power_of_two;
//     table_deref->current_size = 0;
//     table_deref->max_size_allowed = EXTEND_LOAD_FACTOR * get_max_size(table_deref);

//     table_deref->array = (Node **)calloc(1 << (*tablee)->max_size_power_of_two, sizeof(Node *));
//     table_deref->element_size = element_size;
// }

// // Function to free the memory used by the hash table
// void hashmap_destroy(HashTable *table)
// {
//     size_t max_size = 1 << table->max_size_power_of_two;
//     for (size_t i = 0; i < max_size; ++i)
//     {
//         Node *current = table->array[i];
//         while (current != NULL)
//         {
//             printf("should not come here\n");
//             Node *temp = current;
//             current = current->next;

//             destroy_node(temp);
//         }
//     }

//     assert(table->array != NULL);
//     assert(table != NULL);
//     free(table->array);
//     free(table);
// }

// ///////////////////&
// /////PRIVATE FUNCTIONS
// ////////////////////

// void hashmap_resize(HashTable **tablee, size_t power_of_two)
// {
//     HashTable *table = *tablee;
//     assert(power_of_two > 0);

//     if (table->current_size > ((size_t)1 << power_of_two)) // shrink hashmap
//     {
//     }
//     else // extend map
//     {
//         HashTable *new_table;
//         hashmap_init(&new_table, power_of_two + 1, sizeof(int));
//         size_t power_of_two = new_table->max_size_power_of_two;

//         for (size_t i = 0; i < get_max_size(table); ++i)
//         {
//             Node *current = table->array[i];
//             while (current != NULL)
//             {
//                 // OPTIMIZER CAN BE MADE, HAVE A NODE SAVE THE AMOUNT OF modules it took for it to get index
//                 // then when you resize, you can just calculate the new place without doing new hash cause u know calculate the index to %

//                 // OPTIMIZER , POWER OF TWO MAGIC
//                 Node *temp = current;
//                 current = current->next;

//                 char *key = temp->pair.key;
//                 printf("Key: %s\n", key);
//                 size_t index = calculate_modulus(xxHash32(key, strlen(key), 0), power_of_two);

//                 temp->next = new_table->array[index];
//                 new_table->array[index] = temp;
//             }
//         }
//         free((*tablee)->array);
//         free((*tablee));

//         *tablee = new_table;
//     }
// }

// void destroy_node(Node *node)
// {
//     assert(node != NULL);

//     free(node);
// }

// size_t get_max_size(HashTable *table)
// {
//     return (1 << table->max_size_power_of_two);
// }

// #define PRIME32_1 2654435761U
// #define PRIME32_2 2246822519U
// #define PRIME32_3 3266489917U
// #define PRIME32_4 668265263U
// #define PRIME32_5 374761393U

// uint32_t xxHash32(const void *input, size_t length, uint32_t seed)
// {
//     assert(input != NULL);
//     assert(length > 0);
//     const uint8_t *p = (const uint8_t *)input;
//     const uint8_t *end = p + length;
//     uint32_t h32;

//     if (length >= 16)
//     {
//         const uint8_t *limit = end - 16;
//         uint32_t v1 = seed + PRIME32_1 + PRIME32_2;
//         uint32_t v2 = seed + PRIME32_2;
//         uint32_t v3 = seed;
//         uint32_t v4 = seed - PRIME32_1;
//         do
//         {
//             v1 = XXH32_round(v1, XXH_read32(p));
//             p += 4;
//             v2 = XXH32_round(v2, XXH_read32(p));
//             p += 4;
//             v3 = XXH32_round(v3, XXH_read32(p));
//             p += 4;
//             v4 = XXH32_round(v4, XXH_read32(p));
//             p += 4;
//         } while (p <= limit);

//         h32 = XXH32_mergeAccs(v1, v2, v3, v4);
//     }
//     else
//     {
//         h32 = seed + PRIME32_5;
//     }

//     h32 += (uint32_t)length;

//     while (p + 4 <= end)
//     {
//         h32 += XXH_read32(p) * PRIME32_3;
//         h32 = XXH32_rotl(h32, 17) * PRIME32_4;
//         p += 4;
//     }

//     while (p < end)
//     {
//         h32 += (*p++) * PRIME32_5;
//         h32 = XXH32_rotl(h32, 11) * PRIME32_1;
//     }

//     h32 ^= h32 >> 15;
//     h32 *= PRIME32_2;
//     h32 ^= h32 >> 13;
//     h32 *= PRIME32_3;
//     h32 ^= h32 >> 16;

//     return h32;
// }

// // Helper functions

// uint32_t XXH32_rotl(uint32_t x, int r)
// {
//     return (x << r) | (x >> (32 - r));
// }

// uint32_t XXH32_round(uint32_t acc, uint32_t input)
// {
//     acc += input * PRIME32_2;
//     acc = XXH32_rotl(acc, 13);
//     acc *= PRIME32_1;
//     return acc;
// }

// uint32_t XXH32_mergeAccs(uint32_t acc1, uint32_t acc2, uint32_t acc3, uint32_t acc4)
// {
//     acc1 = XXH32_round(acc1, acc2);
//     acc1 = XXH32_round(acc1, acc3);
//     acc1 = XXH32_round(acc1, acc4);
//     return acc1;
// }

// uint32_t XXH_read32(const void *memPtr)
// {
//     return *(const uint32_t *)memPtr;
// }

// int is_equal_key(const Node *one, const char *key)
// {

//     char *key_one = one->pair.key;

//     if (strcmp(key_one, key) == 0)
//     {
//         return 1;
//     }
//     return 0;
// }

// size_t calculate_modulus(int value, size_t powerOfTwo)
// {
//     return (size_t)value & ((1 << powerOfTwo) - 1);
// }