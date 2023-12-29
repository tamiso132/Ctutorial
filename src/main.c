#include <stddef.h>
#include <stdio.h>

#include "hello/hello.h"
#include "list/linkedlist.h"

print_int_list(LinkedList *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        int deref = *((int *)current->data);
        printf("Hello: %d\n", deref);
        current = current->next;
    }
}

int main(int argc, char const *argv[])
{
    LinkedList *list = list_init();
    int b = 10, a = 20, c = 100;
    list_push(list, &b);
    list_push(list, &a);
    list_push(list, &c);

    list_pop(list);

    print_int_list(list);

    return 0;
}
