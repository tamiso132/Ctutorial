#include <stdio.h>
#include "hashmap.h"
#include "internalhash.h"

// to make this even faster, when creating type, use a macro so it is like generic
// right now we make indirection with a

// Definition of struct HashTable
struct HashTable
{
    size_t element_size;
    size_t max_size_power_of_two;
    size_t current_size;
    Node **array;
};

static const float EXTEND_LOAD_FACTOR = 0.7;

#define GET_FAILED INT32_MAX - 1

// private function
void hashmap_resize(HashTable **tablee, size_t new_size);
void hashmap_insert_resize(HashTable *table, Node *node_insert, int hash_index);
size_t get_max_size(HashTable *table);

// Function to insert a key-value pair into the hash table
void hashmap_insert(HashTable **table, const char *key, int value)
{
    assert(key != NULL);
    assert(*table != NULL);
    int n_index = xxHash32(key, strlen(key), 0);

    size_t table_max_size = get_max_size(*table);

    size_t index = calculate_modulus(n_index, (*table)->max_size_power_of_two); // FIX THIS LATER

    KeyValuePair *pair = create_pair(key, value);

    Node *new_node = create_node(pair);
    assert(new_node != NULL); // Check if create_node was successful

    assert((*table) != NULL);
    assert((*table)->array != NULL);
    assert(table_max_size > 0);

    if ((*table)->array[index] == NULL)
    {
        (*table)->array[index] = new_node;
        (*table)->array[index]->next = NULL;
    }
    else
    {
        new_node->next = (*table)->array[index];
        (*table)->array[index] = new_node;
    }
    (*table)->current_size++;
    if ((*table)->current_size > table_max_size * EXTEND_LOAD_FACTOR)
    {
        hashmap_resize(table, (*table)->max_size_power_of_two);
    }
}

int hashmap_remove(HashTable *table, const char *key) // dont shrink during remove, do it during get
{
    size_t hash_index = calculate_modulus(xxHash32(key, strlen(key), 0), table->max_size_power_of_two);

    if (table->array[hash_index] != NULL)
    {
        Node *node = table->array[hash_index];
        Node *prev = table->array[hash_index];

        assert(&node->pair != NULL);
        assert(&node->pair.key != NULL);
        assert(&node->pair.value != NULL);

        if (is_equal_key(node, key))
        {
            Node *temp = table->array[hash_index];
            table->array[hash_index] = node->next;
            table->current_size--;
            destroy_node(temp);
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
                table->current_size--;
                return 1;
            }
            prev = node;
            node = node->next;
        }
    }
    return -1;
}

// return -1 if not found
int hashmap_get(const HashTable *table, const char *key)
{
    assert(key != NULL);
    size_t index = calculate_modulus(xxHash32(key, strlen(key), 0), table->max_size_power_of_two);

    // Traverse the linked list to find the key
    Node *current = table->array[index];
    while (current != NULL)
    {
        if (is_equal_key(current, key))
        {
            return current->pair->value;
        }
        current = current->next;
    }

    // Key not found
    return GET_FAILED;
}

// Function to create a new hash table
void hashmap_init(HashTable **tablee, uint32_t power_of_two, size_t element_size)
{
    *tablee = malloc(sizeof(HashTable));
    (*tablee)->max_size_power_of_two = power_of_two;
    (*tablee)->current_size = 0;
    (*tablee)->array = (Node **)calloc(1 << (*tablee)->max_size_power_of_two, sizeof(Node *));
    (*tablee)->element_size = element_size;

    assert(*tablee != NULL);
    assert((*tablee) != NULL);
}

// Function to free the memory used by the hash table
void hashmap_destroy(HashTable *table)
{
    size_t max_size = 1 << table->max_size_power_of_two;
    for (size_t i = 0; i < max_size; ++i)
    {
        Node *current = table->array[i];
        while (current != NULL)
        {
            printf("should not come here\n");
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

void hashmap_resize(HashTable **tablee, size_t power_of_two)
{
    HashTable *table = *tablee;
    assert(power_of_two > 0);

    if (table->current_size > ((size_t)1 << power_of_two)) // shrink hashmap
    {
    }
    else // extend map
    {
        HashTable *new_table;
        hashmap_init(&new_table, power_of_two + 1, sizeof(int));

        for (size_t i = 0; i < get_max_size(table); ++i)
        {
            Node *current = table->array[i];
            while (current != NULL)
            {
                // OPTIMIZER CAN BE MADE, HAVE A NODE SAVE THE AMOUNT OF modules it took for it to get index
                // then when you resize, you can just calculate the new place without doing new hash cause u know calculate the index to %

                // OPTIMIZER , POWER OF TWO MAGIC
                Node *temp = current;
                current = current->next;

                assert(temp != NULL);
                assert(temp->pair.key != NULL);
                assert(new_table != NULL);
                hashmap_insert(&new_table, temp->pair->key, temp->pair->value);
                destroy_node(temp);
            }
        }
        free((*tablee)->array);
        free((*tablee));

        *tablee = new_table;
    }
}

void hashmap_insert_resize(HashTable *table, Node *node_insert, int hash_index)
{

    if (table->array[hash_index] == NULL)
    {
        table->array[hash_index] = node_insert;
        table->array[hash_index]->next = NULL;
    }
    else
    {
        node_insert->next = table->array[hash_index];
        table->array[hash_index] = node_insert;
    }

    assert(table->array[hash_index] != NULL);
    table->current_size++;
}

size_t get_max_size(HashTable *table)
{
    size_t max_size = (1 << table->max_size_power_of_two);
    return max_size;
}
