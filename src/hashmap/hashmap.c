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

static void hashmapU32_resize(HashmapU32 *table);
static void hashmapU64_resize(HashmapU64 *table);

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

void hashmapU32_init(HashmapU32 *table)
{
    table->max_size = 1 << 4;
    table->array = (MyNodeU32 **)calloc(table->max_size, sizeof(MyNodeU32));
    table->current_size = 0;
    table->load_max_size = LOAD_FACTOR * table->max_size;
}

void hashmapU64_init(HashmapU64 *table)
{
    table->max_size = 1 << 4;
    table->array = (MyNodeU64 **)calloc(table->max_size, sizeof(MyNodeU32));
    table->current_size = 0;
    table->load_max_size = LOAD_FACTOR * table->max_size;
}

void hashmapU32_insert(HashmapU32 *table, uint32_t key, void *value)
{
    uint32_t index = (uint64_t)(XXH64((void *)&key, sizeof(uint32_t), 0) & ((uint64_t)table->max_size - 1));

    MyNodeU32 *node = (MyNodeU32 *)malloc(sizeof(MyNodeU32));
    node->next = table->array[index];
    node->value = value;
    node->key = key;
    table->array[index] = node;
    table->current_size++;

    if (table->load_max_size < table->current_size)
    {
        hashmapU32_resize(table);
    }
}

void hashmapU64_insert(HashmapU64 *table, uint64_t key, void *value)
{
    uint32_t index = (uint64_t)(XXH64((void *)&key, sizeof(uint32_t), 0) & ((uint64_t)table->max_size - 1));

    MyNodeU64 *node = (MyNodeU64 *)malloc(sizeof(MyNodeU64));
    node->next = table->array[index];
    node->value = value;
    node->key = key;
    table->array[index] = node;
    table->current_size++;

    if (table->load_max_size < table->current_size)
    {
        hashmapU64_resize(table);
    }
}

void *hashmapU32_remove(HashmapU32 *table, uint32_t key)
{
    uint32_t index = (uint64_t)(XXH64((void *)&key, sizeof(uint32_t), 0) & ((uint64_t)table->max_size - 1));

    MyNodeU32 *curr = table->array[index];

    if (curr != NULL)
    {
        if (curr->key == key)
        {
            table->current_size--;
            void *temp = curr->value;
            free(curr);
            table->array[index] = NULL;
            return temp;
        }
        curr = curr->next;
        MyNodeU32 *prev = curr;
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
    return NULL;
}

void *hashmapU64_remove(HashmapU64 *table, uint64_t key)
{
    uint32_t index = (uint64_t)(XXH64((void *)&key, sizeof(uint32_t), 0) & ((uint64_t)table->max_size - 1));

    MyNodeU64 *curr = table->array[index];

    if (curr != NULL)
    {
        if (curr->key == key)
        {
            table->current_size--;
            void *temp = curr->value;
            free(curr);
            table->array[index] = NULL;
            return temp;
        }
        curr = curr->next;
        MyNodeU64 *prev = curr;
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
    return NULL;
}

void *hashmapU32_get(const HashmapU32 *table, uint32_t key)
{
    uint32_t index = (uint64_t)(XXH64((void *)&key, sizeof(uint32_t), 0) & ((uint64_t)table->max_size - 1));
    MyNodeU32 *node = table->array[index];
    while (node != NULL)
    {
        if (node->key == key)
        {
            return node->value;
        }
        node = node->next;
    }

    return NULL;
}

void *hashmapU64_get(const HashmapU64 *table, uint64_t key)
{
    uint64_t index = (uint64_t)(XXH64((void *)&key, sizeof(uint64_t), 0) & ((uint64_t)table->max_size - 1));
    MyNodeU64 *node = table->array[index];
    while (node != NULL)
    {
        if (node->key == key)
        {
            return node->value;
        }
        node = node->next;
    }

    return NULL;
}

static void hashmapU32_resize(HashmapU32 *table)
{
    uint32_t new_pow_2 = tamiso_log2(table->max_size) + 1;
    MyNodeU32 **array = calloc(1 << new_pow_2, sizeof(MyNodeU32));

    for (uint32_t i = 0; i < table->max_size; i++)
    {
        MyNodeU32 *curr = table->array[i];

        while (curr != NULL)
        {

            uint32_t index =
                XXH64(&curr->key, sizeof(curr->key), 0) & ((1 << new_pow_2) - 1);

            MyNodeU32 *temp = curr->next;
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

static void hashmapU64_resize(HashmapU64 *table)
{
    uint64_t new_pow_2 = tamiso_log2(table->max_size) + 1;
    MyNodeU64 **array = calloc(1 << new_pow_2, sizeof(MyNodeU64));

    for (uint32_t i = 0; i < table->max_size; i++)
    {
        MyNodeU64 *curr = table->array[i];

        while (curr != NULL)
        {

            uint32_t index =
                XXH64(&curr->key, sizeof(curr->key), 0) & ((1 << new_pow_2) - 1);

            MyNodeU64 *temp = curr->next;
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

void hashmapU32_destroy(HashmapU32 *table)
{
    for (uint32_t i = 0; i < table->max_size - 1; i++)
    {
        if (table->array != NULL)
        {
            MyNodeU32 *node = table->array[i];
            while (node != NULL)
            {
                MyNodeU32 *temp = node;
                node = node->next;

                free(temp->value);
                free(temp);
            }
        }
    }
    free(table->array);
}

void hashmapU64_destroy(HashmapU64 *table)
{
    for (uint32_t i = 0; i < table->max_size - 1; i++)
    {
        if (table->array != NULL)
        {
            MyNodeU64 *node = table->array[i];
            while (node != NULL)
            {
                MyNodeU64 *temp = node;
                node = node->next;

                free(temp->value);
                free(temp);
            }
        }
    }
    free(table->array);
}
