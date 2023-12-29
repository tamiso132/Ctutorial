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
        current = current->next;
    }
}

int main(int argc, char const *argv[])
{
    LinkedList **listt;
    list_init(listt);
    LinkedList *list = listt;
    int b = 10, a = 20, c = 100;
    list_push(list, &b);
    list_push(list, &a);
    list_push(list, &c);

    int peek = *((int *)list_pop_peek(list));

    print_int_list(list);
    return 0;
}
