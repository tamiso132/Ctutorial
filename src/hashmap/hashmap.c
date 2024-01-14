#include <stdlib.h>
#include <stdio.h>

#include "hashmap.h"
#include "xxhash.h"

static double LOAD_FACTOR = 0.6;

static uint8_t tamiso_log2(uint32_t v);
static void hashmap_resize(Hashmap *table);

void hashmap_init(Hashmap *table)
{
    table->max_size = 1 << 4;
    table->array = (MyNode **)calloc(table->max_size, sizeof(MyNode));
    table->current_size = 0;
    table->load_max_size = LOAD_FACTOR * table->max_size;
}

Hashmap *hashmap_heap_init()
{
    Hashmap *table = malloc(sizeof(Hashmap));
    hashmap_init(table);
}

void hashmap_insert(Hashmap *table, uint32_t key, uint32_t value)
{
    uint32_t index = (uint64_t)(XXH64((void *)&key, sizeof(uint32_t), 0) & ((uint64_t)table->max_size - 1));

    MyNode *node = (MyNode *)malloc(sizeof(MyNode));
    node->next = table->array[index];
    node->value = value;
    node->key = key;
    table->array[index] = node;
    table->current_size++;

    if (table->load_max_size < table->current_size)
    {
        hashmap_resize(table);
    }
}

void hashmap_remove(Hashmap *table, uint32_t key)
{
    uint32_t index = (uint64_t)(XXH64((void *)&key, sizeof(uint32_t), 0) & ((uint64_t)table->max_size - 1));

    MyNode *curr = table->array[index];

    if (curr != NULL)
    {
        if (curr->key == key)
        {
            table->current_size--;
            free(curr);
            table->array[index] = NULL;
            return;
        }
        curr = curr->next;
        MyNode *prev = curr;
        while (curr != NULL)
        {
            if (curr->key == key)
            {
                table->current_size--;
                prev->next = curr->next;
                free(curr);
                return;
            }

            prev = curr;
            curr = curr->next;
        }
    }
}

uint32_t hashmap_get(const Hashmap *table, uint32_t key)
{
    uint32_t index = (uint64_t)(XXH64((void *)&key, sizeof(uint32_t), 0) & ((uint64_t)table->max_size - 1));
    MyNode *node = table->array[index];
    int counter;
    while (node != NULL)
    {
        if (node->key == key)
        {
            return node->value;
        }
        node = node->next;
    }

    return 0;
}

static void hashmap_resize(Hashmap *table)
{
    uint32_t new_pow_2 = tamiso_log2(table->max_size) + 1;
    MyNode **array = calloc(1 << new_pow_2, sizeof(MyNode));

    for (uint32_t i = 0; i < table->max_size; i++)
    {
        MyNode *curr = table->array[i];

        while (curr != NULL)
        {

            uint32_t index = XXH64(&curr->key, sizeof(curr->key), 0) & ((1 << new_pow_2) - 1);
            curr->next = array[index];
            array[index] = curr;

            curr = curr->next;
        }
    }

    free(table->array);
    table->array = array;
    table->max_size = 1 << new_pow_2;
    table->load_max_size = LOAD_FACTOR * table->max_size;
}

void hashmap_destroy(Hashmap *table)
{
    for (uint32_t i = 0; i < table->max_size - 1; i++)
    {
        if (table->array != NULL)
        {
            MyNode *node = table->array[i];
            while (node != NULL)
            {
                MyNode *temp = node;
                node = node->next;

                free(temp);
            }
        }
    }
    free(table->array);
}

static uint8_t tamiso_log2(uint32_t v)
{
    static const uint8_t log2table[32] =
        {0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
         8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31};

    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    return log2table[(uint32_t)(v * 0x07C4ACDDU) >> 27];
}
