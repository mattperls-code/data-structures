#include <stdio.h>

#include "binary-search-tree.h"

int main()
{
    struct binary_search_tree* my_tree = NULL;

    printf("tree height: %i\n", binary_search_tree_height(my_tree));

    init_binary_search_tree(&my_tree, 4, "d");

    printf("tree has 2: %s\n", binary_search_tree_has(my_tree, 2) ? "true" : "false");
    printf("tree has 4: %s\n", binary_search_tree_has(my_tree, 4) ? "true" : "false");

    printf("tree height: %i\n", binary_search_tree_height(my_tree));

    binary_search_tree_set(my_tree, -1, "Hello World");
    binary_search_tree_set(my_tree, 2, "b");
    binary_search_tree_set(my_tree, 6, "h");
    binary_search_tree_set(my_tree, 5, "e");

    printf("tree value at 5: %s\n", binary_search_tree_get(my_tree, 5));

    printf("tree height: %i\n", binary_search_tree_height(my_tree));

    binary_search_tree_inorder_print(my_tree);

    binary_search_tree_remove(my_tree, -1);
    binary_search_tree_set(my_tree, 6, "f");

    binary_search_tree_set(my_tree, 1, "a");
    binary_search_tree_set(my_tree, 3, "c");

    printf("tree height: %i\n", binary_search_tree_height(my_tree));

    binary_search_tree_inorder_print(my_tree);

    return 0;
};