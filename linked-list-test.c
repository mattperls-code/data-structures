#include <stdio.h>

#include "linked-list.h"

void print_node(struct linked_list* node)
{
    if (node == NULL)
    {
        printf("empty node. address: %p\n", node);

        return;
    };

    printf("address: %p, data: %i, next: %p\n", node, node->data, node->next);
};

int main()
{
    struct linked_list* my_list = NULL;

    init_linked_list(&my_list, 10);

    linked_list_push(my_list, 20);
    linked_list_push(my_list, 30);

    linked_list_add(my_list, 40, 1);

    linked_list_remove(my_list, 2);
    linked_list_pop(my_list);
    
    for (int i = 0;i<linked_list_size(my_list);i++)
    {
        printf("item at index %i: %i\n", i, linked_list_get(my_list, i));
    };

    return 0;
};