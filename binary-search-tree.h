#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdbool.h>

struct binary_search_tree
{
    int key;
    char* value;

    struct binary_search_tree* left;
    struct binary_search_tree* right;
};

void init_binary_search_tree(struct binary_search_tree** tree, const int root_key, char* value);

void cleanup_binary_search_tree(struct binary_search_tree* tree);

int binary_search_tree_height(const struct binary_search_tree* tree);

bool binary_search_tree_has(const struct binary_search_tree* tree, const int key);

char* binary_search_tree_get(const struct binary_search_tree* tree, const int key);

void binary_search_tree_set(struct binary_search_tree* tree, const int key, char* value);

char* binary_search_tree_remove(struct binary_search_tree* tree, const int key);

void binary_search_tree_inorder_print(const struct binary_search_tree* tree);

#endif