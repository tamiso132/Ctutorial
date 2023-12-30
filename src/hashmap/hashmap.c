#include <stdio.h>

#include "hashmap.h"
#include "internalhash.h"

// to make this even faster, when creating type, use a macro so it is like generic
// right now we make indirection with a

// Definition of struct HashTable
struct HashTable
{
    size_t element_size;
    size_t size;
    Node **array;
};

// Function to insert a key-value pair into the hash table
void hashmap_insert(HashTable *table, const char *key, void *value)
{
    assert(key != NULL);
    printf("String: %s\n", key);
    int index = xxHash32(key, strlen(key), 0) % table->size;

    KeyValuePair *pair = create_pair(key, value, table->element_size);

    Node *new_node = create_node(pair);
    assert(new_node != NULL); // Check if create_node was successful

    assert(table != NULL);
    assert(table->array != NULL);
    assert(table->size > 0);

    if (table->array[index] == NULL)
    {
        table->array[index] = new_node;
        table->array[index]->next = NULL;
    }
    else
    {
        printf("collision now\n");
        new_node->next = table->array[index];
        table->array[index] = new_node;
    }

    // assert(hashmap_get(table, key) != NULL); // Check if insertion was successful
}

int hashmap_remove(HashTable *table, const char *key)
{
    size_t hash_index = xxHash32(key, table->size, 0) % table->size;

    if (table->array[hash_index] != NULL)
    {
        Node *node = table->array[hash_index];
        Node *prev = table->array[hash_index];

        assert(&node->pair != NULL);
        assert(&node->pair.key != NULL);
        assert(&node->pair.value != NULL);

        if (is_equal_key(node, key))
        {
            table->array[hash_index] = node->next;
            return 1;
        }

        prev = node;
        node = node->next;

        while (node != NULL)
        {
            assert(&node->pair != NULL);
            assert(&node->pair.key != NULL);
            assert(&node->pair.value != NULL);

            if (is_equal_key(node, key))
            {
                prev->next = node->next;
                destroy_node(node);
                return 1;
            }
            prev = node;
            node = node->next;
        }
    }
    return -1;
}

// return -1 if not found
void *hashmap_get(const HashTable *table, const char *key)
{
    assert(key != NULL);
    size_t index = xxHash32(key, table->size, 0) % table->size;

    // Traverse the linked list to find the key
    Node *current = table->array[index];
    while (current != NULL)
    {
        if (is_equal_key(current, key))
        {
            return current->pair.value;
        }
        current = current->next;
    }

    // Key not found
    return (void *)-1;
}

// Function to create a new hash table
void hashmap_init(HashTable **tablee, size_t size, size_t element_size)
{
    *tablee = malloc(sizeof(HashTable));
    (*tablee)->size = size;
    (*tablee)->array = (Node **)calloc(size, sizeof(Node *));
    (*tablee)->element_size = element_size;

    assert(*tablee != NULL);
    assert((*tablee) != NULL);
}

// Function to free the memory used by the hash table
void hashmap_destroy(HashTable *table)
{
    for (size_t i = 0; i < table->size; ++i)
    {
        Node *current = table->array[i];
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;

            destroy_node(temp);
        }
    }

    assert(table->array != NULL);
    assert(table != NULL);
    free(table->array);
    free(table);
}
