#pragma once

#define DEFINE_HASHMAP_HEADER(name, key_type, value_type)            \
    typedef struct name##Node                                        \
    {                                                                \
        struct name##Node *next;                                     \
        key_type key;                                                \
        value_type value;                                            \
    } name##Node;                                                    \
                                                                     \
    typedef struct name                                              \
    {                                                                \
        uint64_t max_size;                                           \
        name##Node **array;                                          \
        uint64_t current_size;                                       \
        uint64_t load_max_size;                                      \
    } name;                                                          \
    void name##_init(name *table);                                   \
    void name##_insert(name *table, key_type key, value_type value); \
    void name##_destroy(name *table);                                \
    void name##_remove(name *table, key_type key);                   \
    value_type *name##_get(const name *table, key_type key);

#define DEFINE_HASHMAP_METHODS(name, key_type, value_type)                                                       \
                                                                                                                 \
    static void name##_resize(name *table);                                                                      \
                                                                                                                 \
    void name##_init(name *table)                                                                                \
    {                                                                                                            \
        table->max_size = 1 << 4;                                                                                \
        table->array = (name##Node **)calloc(table->max_size, sizeof(name##Node *));                             \
        table->current_size = 0;                                                                                 \
        table->load_max_size = 0.7 * table->max_size;                                                            \
    }                                                                                                            \
                                                                                                                 \
    void name##_insert(name *table, key_type key, value_type value)                                              \
    {                                                                                                            \
        uint32_t index = (uint64_t)(XXH64((void *)&key, sizeof(key_type), 0) & ((uint64_t)table->max_size - 1)); \
        name##Node *node = (name##Node *)malloc(sizeof(name##Node));                                             \
        node->next = table->array[index];                                                                        \
        node->value = value;                                                                                     \
        node->key = key;                                                                                         \
        table->array[index] = node;                                                                              \
        table->current_size++;                                                                                   \
        if (table->load_max_size < table->current_size)                                                          \
        {                                                                                                        \
            name##_resize(table);                                                                                \
        }                                                                                                        \
    }                                                                                                            \
                                                                                                                 \
    static void name##_resize(name *table)                                                                       \
    {                                                                                                            \
        uint32_t new_pow_2 = tamiso_log2(table->max_size) + 1;                                                   \
        name##Node **array = calloc(1 << new_pow_2, sizeof(name##Node *));                                       \
                                                                                                                 \
        for (uint32_t i = 0; i < table->max_size; i++)                                                           \
        {                                                                                                        \
            name##Node *curr = table->array[i];                                                                  \
                                                                                                                 \
            while (curr != NULL)                                                                                 \
            {                                                                                                    \
                uint32_t index = XXH64(&curr->key, sizeof(curr->key), 0) & ((1 << new_pow_2) - 1);               \
                name##Node *temp = curr;                                                                         \
                curr = curr->next;                                                                               \
                temp->next = array[index];                                                                       \
                array[index] = temp;                                                                             \
            }                                                                                                    \
        }                                                                                                        \
                                                                                                                 \
        free(table->array);                                                                                      \
        table->array = array;                                                                                    \
        table->max_size = 1 << new_pow_2;                                                                        \
        table->load_max_size = 0.7 * table->max_size;                                                            \
    }                                                                                                            \
                                                                                                                 \
    void name##_destroy(name *table)                                                                             \
    {                                                                                                            \
        for (uint32_t i = 0; i < table->max_size - 1; i++)                                                       \
        {                                                                                                        \
            if (table->array != NULL)                                                                            \
            {                                                                                                    \
                name##Node *node = table->array[i];                                                              \
                while (node != NULL)                                                                             \
                {                                                                                                \
                    name##Node *temp = node;                                                                     \
                    node = node->next;                                                                           \
                    free(temp);                                                                                  \
                }                                                                                                \
            }                                                                                                    \
        }                                                                                                        \
        free(table->array);                                                                                      \
    }                                                                                                            \
                                                                                                                 \
    value_type *name##_get(const name *table, key_type key)                                                      \
    {                                                                                                            \
        uint32_t index = (uint64_t)(XXH64((void *)&key, sizeof(key_type), 0) & ((uint64_t)table->max_size - 1)); \
        name##Node *node = table->array[index];                                                                  \
        while (node != NULL)                                                                                     \
        {                                                                                                        \
            if (node->key == key)                                                                                \
            {                                                                                                    \
                return &node->value;                                                                             \
            }                                                                                                    \
            node = node->next;                                                                                   \
        }                                                                                                        \
        return NULL;                                                                                             \
    }                                                                                                            \
                                                                                                                 \
    void name##_remove(name *table, key_type key)                                                                \
    {                                                                                                            \
        uint32_t index = (uint64_t)(XXH64((void *)&key, sizeof(key_type), 0) & ((uint64_t)table->max_size - 1)); \
        name##Node *curr = table->array[index];                                                                  \
                                                                                                                 \
        if (curr != NULL)                                                                                        \
        {                                                                                                        \
            if (curr->key == key)                                                                                \
            {                                                                                                    \
                table->current_size--;                                                                           \
                free(curr);                                                                                      \
                table->array[index] = NULL;                                                                      \
                return;                                                                                          \
            }                                                                                                    \
            curr = curr->next;                                                                                   \
            name##Node *prev = curr;                                                                             \
            while (curr != NULL)                                                                                 \
            {                                                                                                    \
                if (curr->key == key)                                                                            \
                {                                                                                                \
                    table->current_size--;                                                                       \
                    prev->next = curr->next;                                                                     \
                    free(curr);                                                                                  \
                    return;                                                                                      \
                }                                                                                                \
                prev = curr;                                                                                     \
                curr = curr->next;                                                                               \
            }                                                                                                    \
        }                                                                                                        \
    }

#define DEFINE_SET_HEADER(name, key_type)          \
    typedef struct name##Node                      \
    {                                              \
        struct name##Node *next;                   \
        key_type key;                              \
    } name##Node;                                  \
                                                   \
    typedef struct name                            \
    {                                              \
        uint64_t max_size;                         \
        name##Node **array;                        \
        uint64_t current_size;                     \
        uint64_t load_max_size;                    \
    } name;                                        \
    void name##_init(name *table);                 \
    void name##_insert(name *table, key_type key); \
    void name##_destroy(name *table);              \
    void name##_remove(name *table, key_type key); \
    key_type *name##_get(const name *table, key_type key);

#define DEFINE_SET_METHODS(name, key_type)                                                                       \
                                                                                                                 \
    static void name##_resize(name *table);                                                                      \
                                                                                                                 \
    void name##_init(name *table)                                                                                \
    {                                                                                                            \
        table->max_size = 1 << 4;                                                                                \
        table->array = (name##Node **)calloc(table->max_size, sizeof(name##Node *));                             \
        table->current_size = 0;                                                                                 \
        table->load_max_size = 0.7 * table->max_size;                                                            \
    }                                                                                                            \
                                                                                                                 \
    void name##_insert(name *table, key_type key)                                                                \
    {                                                                                                            \
        uint32_t index = (uint64_t)(XXH64((void *)&key, sizeof(key_type), 0) & ((uint64_t)table->max_size - 1)); \
        name##Node *node = (name##Node *)malloc(sizeof(name##Node));                                             \
        node->next = table->array[index];                                                                        \
        node->key = key;                                                                                         \
        table->array[index] = node;                                                                              \
        table->current_size++;                                                                                   \
        if (table->load_max_size < table->current_size)                                                          \
        {                                                                                                        \
            name##_resize(table);                                                                                \
        }                                                                                                        \
    }                                                                                                            \
                                                                                                                 \
    static void name##_resize(name *table)                                                                       \
    {                                                                                                            \
        uint32_t new_pow_2 = tamiso_log2(table->max_size) + 1;                                                   \
        name##Node **array = calloc(1 << new_pow_2, sizeof(name##Node *));                                       \
                                                                                                                 \
        for (uint32_t i = 0; i < table->max_size; i++)                                                           \
        {                                                                                                        \
            name##Node *curr = table->array[i];                                                                  \
                                                                                                                 \
            while (curr != NULL)                                                                                 \
            {                                                                                                    \
                uint32_t index = XXH64(&curr->key, sizeof(curr->key), 0) & ((1 << new_pow_2) - 1);               \
                name##Node *temp = curr;                                                                         \
                curr = curr->next;                                                                               \
                temp->next = array[index];                                                                       \
                array[index] = temp;                                                                             \
            }                                                                                                    \
        }                                                                                                        \
                                                                                                                 \
        free(table->array);                                                                                      \
        table->array = array;                                                                                    \
        table->max_size = 1 << new_pow_2;                                                                        \
        table->load_max_size = LOAD_FACTOR * table->max_size;                                                    \
    }                                                                                                            \
                                                                                                                 \
    void name##_destroy(name *table)                                                                             \
    {                                                                                                            \
        for (uint32_t i = 0; i < table->max_size - 1; i++)                                                       \
        {                                                                                                        \
            if (table->array != NULL)                                                                            \
            {                                                                                                    \
                name##Node *node = table->array[i];                                                              \
                while (node != NULL)                                                                             \
                {                                                                                                \
                    name##Node *temp = node;                                                                     \
                    node = node->next;                                                                           \
                    free(temp);                                                                                  \
                }                                                                                                \
            }                                                                                                    \
        }                                                                                                        \
        free(table->array);                                                                                      \
    }                                                                                                            \
                                                                                                                 \
    key_type *name##_get(const name *table, key_type key)                                                        \
    {                                                                                                            \
        uint32_t index = (uint64_t)(XXH64((void *)&key, sizeof(key_type), 0) & ((uint64_t)table->max_size - 1)); \
        name##Node *node = table->array[index];                                                                  \
        while (node != NULL)                                                                                     \
        {                                                                                                        \
            if (node->key == key)                                                                                \
            {                                                                                                    \
                return &node->key;                                                                               \
            }                                                                                                    \
            node = node->next;                                                                                   \
        }                                                                                                        \
        return NULL;                                                                                             \
    }                                                                                                            \
                                                                                                                 \
    void name##_remove(name *table, key_type key)                                                                \
    {                                                                                                            \
        uint32_t index = (uint64_t)(XXH64((void *)&key, sizeof(key_type), 0) & ((uint64_t)table->max_size - 1)); \
        name##Node *curr = table->array[index];                                                                  \
                                                                                                                 \
        if (curr != NULL)                                                                                        \
        {                                                                                                        \
            if (curr->key == key)                                                                                \
            {                                                                                                    \
                table->current_size--;                                                                           \
                free(curr);                                                                                      \
                table->array[index] = NULL;                                                                      \
                return;                                                                                          \
            }                                                                                                    \
            curr = curr->next;                                                                                   \
            name##Node *prev = curr;                                                                             \
            while (curr != NULL)                                                                                 \
            {                                                                                                    \
                if (curr->key == key)                                                                            \
                {                                                                                                \
                    table->current_size--;                                                                       \
                    prev->next = curr->next;                                                                     \
                    free(curr);                                                                                  \
                    return;                                                                                      \
                }                                                                                                \
                prev = curr;                                                                                     \
                curr = curr->next;                                                                               \
            }                                                                                                    \
        }                                                                                                        \
    }
