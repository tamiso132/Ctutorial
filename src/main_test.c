#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "collection/linkedlist.h"
#include "collection/vector.h"

void list_test()
{
    printf("list test start\n");
    // Create a new linked list
    LinkedList *list;
    list_init(&list);

    printf("Init Done\n");

    if (list == NULL)
    {
        printf("yeppers\n");
    }
    else
    {
        printf("noppers\n");
    }

    // Test list_push
    int data1 = 42;
    list_push(list, &data1);
    assert((list)->head != NULL);
    assert((list)->tail != NULL);
    assert((list)->head->data == &data1);
    assert((list)->tail->data == &data1);

    printf("Push Test Done\n");

    // Test list_pop
    void *pop_data = list_pop(list);
    assert(pop_data == &data1);
    assert((list)->head == NULL);
    assert((list)->tail == NULL);

    printf("Pop Test Done\n");

    // Test list_push again
    int data2 = 57;
    list_push(list, &data2);
    assert((list)->head != NULL);
    assert((list)->tail != NULL);
    assert((list)->head->data == &data2);
    assert((list)->tail->data == &data2);

    // Test list_pop_front
    void *pop_front_data = list_pop_front(list);
    assert(pop_front_data == &data2);
    assert((list)->head == NULL);
    assert((list)->tail == NULL);

    printf("Pop Front Test Done\n");

    // Test other functions as needed

    // Test insert functions
    int data3 = 55;
    list_insert(list, 0, &data1);
    list_insert(list, 0, &data2);
    list_insert(list, 0, &data3);

    void *value = list_pop_front(list);
    value = list_pop_front(list);
    value = list_pop_front(list);

    printf("List Insert Done\n");

    // Clean up
    list_delete_all(&list);
    assert(list == NULL);
    printf("list test end\n");
}

void vector_test()
{
    printf("\n\n");
    Vector vector;
    init_vector(&vector, sizeof(int), 1);
    int d1 = 42;
    int d2 = 72;
    int d3 = 100;
    vector_push_element(&vector, &d1);
    vector_push_element(&vector, &d2);
    vector_push_element(&vector, &d3);

    int number = *((char *)vector_get(&vector, 0));
    assert(number == d1);

    number = *((char *)vector_get(&vector, 1));
    assert(number == d2);

    number = *((char *)vector_get(&vector, 2));
    assert(number == d3);

    vector_remove(&vector, 0);
    vector_remove(&vector, 0);
    vector_remove(&vector, 0);

    assert(vector.length == 0);

    vector_push_element(&vector, &d1);
    vector_push_element(&vector, &d2);
    vector_push_element(&vector, &d3);

    vector_remove(&vector, 1);
    number = *((char *)vector_get(&vector, 0));
    assert(number == d1);

    number = *((char *)vector_get(&vector, 1));
    assert(number == d3);

    printf("Finished\n");
}
int main(int argc, char const *argv[])
{
    list_test();
    vector_test();
    return 0;
}
