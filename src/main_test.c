
#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "allocator/alloc.h"
#include "collection/linkedlist.h"
#include "collection/vector.h"
#include "hashmap/hashmap.h"

<<<<<<< HEAD
// void benchmark_operations(size_t num_operations, size_t hashmap_size, int repeat)
// {

//     int repeat_clone = repeat;
//     double insertion_total = 0;
//     double retrive_total = 0;
//     double removal_total = 0;
//     double hash_total = 0;
//     while (repeat_clone > 0)
//     {
//         HashTable *table;
//         size_t i;

//         printf("Number of operations in respective benching %ld\n", num_operations);
//         clock_t start_time = clock();

//         for (i = 0; i < num_operations; ++i)
//         {
//             char key[20];
//             sprintf(key, "key%d", (int)i);

//             xxHash32(key, strlen(key), 0);
//         }

//         clock_t end_time = clock();
//         hash_total += (double)(end_time - start_time) / CLOCKS_PER_SEC;
//         // Benchmark retrievals
//         start_time = clock();

//         // Initialize the hash table
//         hashmap_init(&table, hashmap_size, sizeof(int));
//         // Benchmark insertions
//         start_time = clock();
//         for (i = 0; i < num_operations; ++i)
//         {
//             char key[20];
//             sprintf(key, "key%d", (int)i);
//             int value = i;
//             hashmap_insert(&table, key, value);
//         }
//         end_time = clock();
//         insertion_total += (double)(end_time - start_time) / CLOCKS_PER_SEC;
//         // Benchmark retrievals
//         start_time = clock();
//         for (i = 0; i < num_operations; ++i)
//         {
//             char key[20];
//             sprintf(key, "key%d", (int)i);
//             hashmap_get(table, key);
//         }
//         end_time = clock();
//         retrive_total += (double)(end_time - start_time) / CLOCKS_PER_SEC;
//         // Benchmark removals
//         start_time = clock();
//         for (i = 0; i < num_operations; ++i)
//         {
//             char key[20];
//             sprintf(key, "key%d", (int)i);
//             hashmap_remove(table, key);
//         }
//         end_time = clock();
//         removal_total += (double)(end_time - start_time) / CLOCKS_PER_SEC;

//         // // Destroy the hash table
//         hashmap_destroy(table);
//         repeat_clone--;
//     }
=======
void benchmark_operations(size_t num_operations, size_t hashmap_size, int repeat)
{
    int repeat_clone = repeat;
    double insertion_total = 0;
    double retrive_total = 0;
    double removal_total = 0;
    double hash_total = 0;
    while (repeat_clone > 0)
    {
        HashTable table;
        size_t i;

        printf("Number of operations in respective benching %ld\n", num_operations);
        clock_t start_time = clock();
        for (i = 0; i < num_operations; ++i)
        {
            char key[20];
            sprintf(key, "key%d", (int)i);

            xxHash32(key, strlen(key), 0);
        }
        clock_t end_time = clock();
        hash_total += (double)(end_time - start_time) / CLOCKS_PER_SEC;
        // Benchmark retrievals
        start_time = clock();

        // Initialize the hash table
        hashmap_init(&table, hashmap_size, sizeof(int));
        printf("DESTROY \n");
        // Benchmark insertions
        start_time = clock();
        for (i = 0; i < num_operations; ++i)
        {
            char key[20];
            sprintf(key, "key%d", (int)i);
            int value = i;
            hashmap_insert(&table, key, value);
        }
        end_time = clock();
        insertion_total += (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("DESTROY \n");
        // Benchmark retrievals
        start_time = clock();
        for (i = 0; i < num_operations; ++i)
        {
            char key[20];
            sprintf(key, "key%d", (int)i);
            int val;
            hashmap_get(&table, key, &val);
        }
        end_time = clock();
        retrive_total += (double)(end_time - start_time) / CLOCKS_PER_SEC;
        // Benchmark removals
        start_time = clock();
        for (i = 0; i < num_operations; ++i)
        {
            char key[20];
            sprintf(key, "key%d", (int)i);
            hashmap_remove(&table, key);
        }
        end_time = clock();
        removal_total += (double)(end_time - start_time) / CLOCKS_PER_SEC;

        // // Destroy the hash table
        printf("DESTROY \n");
        hashmap_destroy(&table);
        repeat_clone--;
    }
>>>>>>> 9acac7b0ddef2112aea730d1094ac0275ef62a08

//     printf("\nInsertions took %f seconds\n", insertion_total / repeat);
//     printf("Retrievals took %f seconds\n", retrive_total / repeat);
//     printf("Removals took %f seconds\n\n", removal_total / repeat);
//     printf("hashing took %f seconds\n\n", hash_total / repeat);
// }

void hashmap_test()
{
    // HashTable *hashmap;
    // hashmap_init(&hashmap, 100, sizeof(int));
    // assert(hashmap != NULL);

    // int value_1 = 50;
    // int value_2 = 70;

    // hashmap_insert(hashmap, "example_key", &value_1);
    // hashmap_insert(hashmap, "hello", &value_2);

    // int *val_2 = (int *)hashmap_get(hashmap, "hello");
    // int *val_1 = (int *)hashmap_get(hashmap, "example_key");

    // assert(*val_1 == value_1);
    // assert(*val_2 == value_2);

    // assert(hashmap_remove(hashmap, "hello") == 1);
    // assert(hashmap_remove(hashmap, "hello") == -1);
    // assert(hashmap_remove(hashmap, "helloggggg") == -1);
}

void list_test()
{
    // printf("list test start\n");
    // // Create a new linked list
    // LinkedList *list;
    // list_init(&list);

    // printf("Init Done\n");

    // if (list == NULL)
    // {
    //     printf("yeppers\n");
    // }
    // else
    // {
    //     printf("noppers\n");
    // }

    // // Test list_push
    // int data1 = 42;
    // list_push(list, &data1);
    // assert((list)->head != NULL);
    // assert((list)->tail != NULL);
    // assert((list)->head->data == &data1);
    // assert((list)->tail->data == &data1);

    // printf("Push Test Done\n");

    // // Test list_pop
    // void *pop_data = list_pop(list);
    // assert(pop_data == &data1);
    // assert((list)->head == NULL);
    // assert((list)->tail == NULL);

    // printf("Pop Test Done\n");

    // // Test list_push again
    // int data2 = 57;
    // list_push(list, &data2);
    // assert((list)->head != NULL);
    // assert((list)->tail != NULL);
    // assert((list)->head->data == &data2);
    // assert((list)->tail->data == &data2);

    // // Test list_pop_front
    // void *pop_front_data = list_pop_front(list);
    // assert(pop_front_data == &data2);
    // assert((list)->head == NULL);
    // assert((list)->tail == NULL);

    // printf("Pop Front Test Done\n");

    // // Test other functions as needed

    // // Test insert functions
    // int data3 = 55;
    // list_insert(list, 0, &data1);
    // list_insert(list, 0, &data2);
    // list_insert(list, 0, &data3);

    // list_pop_front(list);
    // list_pop_front(list);
    // list_pop_front(list);

    // printf("List Insert Done\n");

    // // Clean up
    // list_delete_all(&list);
    // assert(list == NULL);
    // printf("list test end\n");
}

// void vector_test()
// {
//     printf("\n\n");
//     Vector vector;
//     init_vector(&vector, sizeof(int), 1);
//     int d1 = 42;
//     int d2 = 72;
//     int d3 = 100;
//     vector_push_element(&vector, &d1);
//     vector_push_element(&vector, &d2);
//     vector_push_element(&vector, &d3);

//     int number = *((char *)vector_get(&vector, 0));
//     assert(number == d1);

//     number = *((char *)vector_get(&vector, 1));
//     assert(number == d2);

//     number = *((char *)vector_get(&vector, 2));
//     assert(number == d3);

//     vector_remove(&vector, 0);
//     vector_remove(&vector, 0);
//     vector_remove(&vector, 0);

//     assert(vector.length == 0);

//     vector_push_element(&vector, &d1);
//     vector_push_element(&vector, &d2);
//     vector_push_element(&vector, &d3);

//     vector_remove(&vector, 1);
//     number = *((char *)vector_get(&vector, 0));
//     assert(number == d1);

//     number = *((char *)vector_get(&vector, 1));
//     assert(number == d3);

//     printf("Finished\n");
// }

#pragma GCC diagnostic ignored "-Wunused-parameter" // for disable main parameter warning
int main(int argc, char const *argv[])
{

<<<<<<< HEAD
=======
    benchmark_operations(1000000, 5, 5);
>>>>>>> 9acac7b0ddef2112aea730d1094ac0275ef62a08
    return 0;
}
#pragma GCC diagnostic warning "-Wunused-parameter"
