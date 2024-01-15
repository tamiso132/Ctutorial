#include "macro.h"
#include <stdlib.h>
#include <stdio.h>

#include "xxhash.h"
#include "hashmap.h"

static double LOAD_FACTOR = 0.6;

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

static void SetU64_resize(SetU64 *table);
void SetU64_init(SetU64 *table)
{
    table->max_size = 1 << 4;
    table->array = (SetU64Node **)calloc(table->max_size, sizeof(SetU64Node *));
    table->current_size = 0;
    table->load_max_size = 0.7 * table->max_size;
}
void SetU64_insert(SetU64 *table, uint64_t key)
{
    uint32_t index = (uint64_t)(XXH64((void *)&key, sizeof(uint64_t), 0) & ((uint64_t)table->max_size - 1));
    SetU64Node *node = (SetU64Node *)malloc(sizeof(SetU64Node));
    node->next = table->array[index];
    node->key = key;
    table->array[index] = node;
    table->current_size++;
    if (table->load_max_size < table->current_size)
    {
        SetU64_resize(table);
    }
}
static void SetU64_resize(SetU64 *table)
{
    uint32_t new_pow_2 = tamiso_log2(table->max_size) + 1;
    SetU64Node **array = calloc(1 << new_pow_2, sizeof(SetU64Node *));
    for (uint32_t i = 0; i < table->max_size; i++)
    {
        SetU64Node *curr = table->array[i];
        while (curr != ((void *)0))
        {
            uint32_t index = XXH64(&curr->key, sizeof(curr->key), 0) & ((1 << new_pow_2) - 1);
            SetU64Node *temp = curr;
            curr = curr->next;
            temp->next = array[index];
            array[index] = temp;
        }
    }
    free(table->array);
    table->array = array;
    table->max_size = 1 << new_pow_2;
    table->load_max_size = LOAD_FACTOR * table->max_size;
}
void SetU64_destroy(SetU64 *table)
{
    for (uint32_t i = 0; i < table->max_size - 1; i++)
    {
        if (table->array != ((void *)0))
        {
            SetU64Node *node = table->array[i];
            while (node != ((void *)0))
            {
                SetU64Node *temp = node;
                node = node->next;
                free(temp);
            }
        }
    }
    free(table->array);
}
uint64_t *SetU64_get(const SetU64 *table, uint64_t key)
{
    uint32_t index = (uint64_t)(XXH64((void *)&key, sizeof(uint64_t), 0) & ((uint64_t)table->max_size - 1));
    SetU64Node *node = table->array[index];
    while (node != ((void *)0))
    {
        if (node->key == key)
        {
            return &node->key;
        }
        node = node->next;
    }
    return NULL;
}
void SetU64_remove(SetU64 *table, uint64_t key)
{
    uint32_t index = (uint64_t)(XXH64((void *)&key, sizeof(uint64_t), 0) & ((uint64_t)table->max_size - 1));
    SetU64Node *curr = table->array[index];
    if (curr != ((void *)0))
    {
        if (curr->key == key)
        {
            table->current_size--;
            free(curr);
            table->array[index] = ((void *)0);
            return;
        }
        curr = curr->next;
        SetU64Node *prev = curr;
        while (curr != ((void *)0))
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

// static uint8_t tamiso_log2(uint32_t v);
// static void hashmap_resize(Hashmap *table);

void hashmapU32_init(Hashmap *table)
{
    table->max_size = 1 << 4;
    table->array = (MyNode **)calloc(table->max_size, sizeof(MyNode));
    table->current_size = 0;
    table->load_max_size = LOAD_FACTOR * table->max_size;
}

void hashmapU32_insert(Hashmap *table, uint32_t key, void *value)
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

void *hashmapU32_remove(Hashmap *table, uint32_t key)
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
                void *val = &curr->value;
                free(curr);

                return val;
            }

            prev = curr;
            curr = curr->next;
        }
    }
}

void *hashmapU32_get(const Hashmap *table, uint32_t key)
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

            uint32_t index =
                XXH64(&curr->key, sizeof(curr->key), 0) & ((1 << new_pow_2) - 1);

            MyNode *temp = curr->next;
            curr->next = array[index];
            array[index] = curr;

            curr = temp;
        }
    }

    free(table->array);
    table->array = array;
    table->max_size = 1 << new_pow_2;
    table->load_max_size = LOAD_FACTOR * table->max_size;
}

void hashmapU32_destroy(Hashmap *table)
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

                free(temp->value);
                free(temp);
            }
        }
    }
    free(table->array);
}
