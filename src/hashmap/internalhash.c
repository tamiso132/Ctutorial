#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "internalhash.h"

#define PRIME32_1 2654435761U
#define PRIME32_2 2246822519U
#define PRIME32_3 3266489917U
#define PRIME32_4 668265263U
#define PRIME32_5 374761393U

uint32_t XXH32_rotl(uint32_t x, int r);
uint32_t XXH32_round(uint32_t acc, uint32_t input);
uint32_t XXH32_mergeAccs(uint32_t acc1, uint32_t acc2, uint32_t acc3, uint32_t acc4);
uint32_t XXH_read32(const void *memPtr);

uint32_t xxHash32(const void *input, size_t length, uint32_t seed)
{
    assert(input != NULL);
    assert(length > 0);
    const uint8_t *p = (const uint8_t *)input;
    const uint8_t *end = p + length;
    uint32_t h32;

    if (length >= 16)
    {
        const uint8_t *limit = end - 16;
        uint32_t v1 = seed + PRIME32_1 + PRIME32_2;
        uint32_t v2 = seed + PRIME32_2;
        uint32_t v3 = seed;
        uint32_t v4 = seed - PRIME32_1;
        do
        {
            v1 = XXH32_round(v1, XXH_read32(p));
            p += 4;
            v2 = XXH32_round(v2, XXH_read32(p));
            p += 4;
            v3 = XXH32_round(v3, XXH_read32(p));
            p += 4;
            v4 = XXH32_round(v4, XXH_read32(p));
            p += 4;
        } while (p <= limit);

        h32 = XXH32_mergeAccs(v1, v2, v3, v4);
    }
    else
    {
        h32 = seed + PRIME32_5;
    }

    h32 += (uint32_t)length;

    while (p + 4 <= end)
    {
        h32 += XXH_read32(p) * PRIME32_3;
        h32 = XXH32_rotl(h32, 17) * PRIME32_4;
        p += 4;
    }

    while (p < end)
    {
        h32 += (*p++) * PRIME32_5;
        h32 = XXH32_rotl(h32, 11) * PRIME32_1;
    }

    h32 ^= h32 >> 15;
    h32 *= PRIME32_2;
    h32 ^= h32 >> 13;
    h32 *= PRIME32_3;
    h32 ^= h32 >> 16;

    return h32;
}

// Function to create a new key-value pair
KeyValuePair *create_pair(const char *key, int value, int element_size)
{
    KeyValuePair *pair = (KeyValuePair *)malloc(sizeof(KeyValuePair));
    pair->key = strdup(key); // strdup allocates memory for the key
    pair->value = value;

    assert(pair->key != NULL);
    return pair;
}

// Function to create a new node
Node *create_node(KeyValuePair *pair)
{
    assert(pair != NULL);
    Node *node = (Node *)malloc(sizeof(Node));
    node->pair = *pair;
    node->next = NULL;

    assert(node != NULL);
    return node;
}
void destroy_node(Node *node)
{
    assert(node->pair.key != NULL);
    assert(node != NULL);

    free(node->pair.key);
    free(node);
}
// Helper functions

uint32_t XXH32_rotl(uint32_t x, int r)
{
    return (x << r) | (x >> (32 - r));
}

uint32_t XXH32_round(uint32_t acc, uint32_t input)
{
    acc += input * PRIME32_2;
    acc = XXH32_rotl(acc, 13);
    acc *= PRIME32_1;
    return acc;
}

uint32_t XXH32_mergeAccs(uint32_t acc1, uint32_t acc2, uint32_t acc3, uint32_t acc4)
{
    acc1 = XXH32_round(acc1, acc2);
    acc1 = XXH32_round(acc1, acc3);
    acc1 = XXH32_round(acc1, acc4);
    return acc1;
}

uint32_t XXH_read32(const void *memPtr)
{
    return *(const uint32_t *)memPtr;
}

int is_equal_key(const Node *one, const char *key)
{
    assert(&one->pair != NULL);
    assert(&one->pair.key != NULL);
    assert(&one->pair.value != NULL);

    char *key_one = one->pair.key;

    if (strcmp(key_one, key) == 0)
    {
        return 1;
    }
    return 0;
}