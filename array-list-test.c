#include <stdio.h>

#include "array-list.h"

int main()
{
    struct array_list my_list;

    init_array_list(&my_list, 4);

    printf("created array. capacity: %i, size: %i\n", my_list.capacity, my_list.size);

    array_list_add(&my_list, 10, 0);
    array_list_add(&my_list, 20, 0);
    array_list_push(&my_list, 30);
    array_list_add(&my_list, 40, 1);
    array_list_add(&my_list, 50, 2);
    array_list_push(&my_list, 60);
    array_list_add(&my_list, 70, 4);

    printf("added items. capacity: %i, size: %i\n", my_list.capacity, my_list.size);

    for (int i = 0;i<my_list.size;i++)
    {
        printf("value at array index %i: %i\n", i, array_list_get(&my_list, i));
    };

    int popped = array_list_pop(&my_list);
    int removedFromIndex3 = array_list_remove(&my_list, 3);

    printf("removed items. capacity: %i, size: %i\n", my_list.capacity, my_list.size);

    printf("popped item: %i\n", popped);
    printf("removed from index 3: %i\n", removedFromIndex3);

    for (int i = 0;i<my_list.size;i++)
    {
        printf("value at array index %i: %i\n", i, array_list_get(&my_list, i));
    };

    return 0;
};