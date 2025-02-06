#include <stdio.h>
#include <stdlib.h>

#include "binary-search-tree.h"

void init_binary_search_tree(struct binary_search_tree** tree, const int root_key, char* value)
{
    *tree = (struct binary_search_tree*) malloc(sizeof(struct binary_search_tree));

    (*tree)->key = root_key;
    (*tree)->value = value;

    (*tree)->left = NULL;
    (*tree)->right = NULL;
};

void cleanup_binary_search_tree(struct binary_search_tree* tree)
{
    if (tree == NULL) return;

    cleanup_binary_search_tree(tree->left);
    cleanup_binary_search_tree(tree->right);

    free(tree);
};

int binary_search_tree_height(const struct binary_search_tree* tree)
{
    if (tree == NULL) return 0;

    int left_subtree_height = binary_search_tree_height(tree->left);
    int right_subtree_height = binary_search_tree_height(tree->right);

    int max_subtree_height = left_subtree_height > right_subtree_height ? left_subtree_height : right_subtree_height;

    return max_subtree_height + 1;
};

bool binary_search_tree_has(const struct binary_search_tree* tree, const int key)
{
    if (tree == NULL) return false;

    if (tree->key == key) return true;
    
    return binary_search_tree_has(key > tree->key ? tree->right : tree->left, key);
};

char* binary_search_tree_get(const struct binary_search_tree* tree, const int key)
{
    if (tree == NULL)
    {
        printf("Could not find key on binary search tree get");
        exit(1);
    };

    if (tree->key == key) return tree->value;

    return binary_search_tree_get(key > tree->key ? tree->right : tree->left, key);
};

void binary_search_tree_set(struct binary_search_tree* tree, const int key, char* value)
{
    if (tree == NULL)
    {
        printf("Cannot set in uninitialized binary search tree");
        exit(1);
    };

    if (tree->key == key)
    {
        tree->value = value;

        return;
    };

    struct binary_search_tree** next_subtree_ptr = key > tree->key ? &tree->right : &tree->left;

    if (*next_subtree_ptr == NULL) init_binary_search_tree(next_subtree_ptr, key, value);
    
    else binary_search_tree_set(*next_subtree_ptr, key, value);
};

bool binary_search_tree_has_max_predecessor(struct binary_search_tree* tree)
{
    if (tree->left == NULL) return false;

    if (tree->left->right == NULL) return false;

    return true;
};

struct binary_search_tree binary_search_tree_remove_max_predecessor(struct binary_search_tree* tree)
{
    struct binary_search_tree* max_predecessor_parent = tree->left;
    struct binary_search_tree* max_predecessor = tree->left->right;

    while (max_predecessor->right != NULL)
    {
        max_predecessor_parent = max_predecessor;

        max_predecessor = max_predecessor->right;
    };

    struct binary_search_tree max_predecessor_data = *max_predecessor;

    max_predecessor_parent->right = NULL;

    free(max_predecessor);

    return max_predecessor_data;
};

bool binary_search_tree_has_min_successor(struct binary_search_tree* tree)
{
    if (tree->right == NULL) return false;

    if (tree->right->left == NULL) return false;

    return true;
};

struct binary_search_tree binary_search_tree_remove_min_successor(struct binary_search_tree* tree)
{
    struct binary_search_tree* min_successor_parent = tree->right;
    struct binary_search_tree* min_successor = tree->right->left;

    while (min_successor->left != NULL)
    {
        min_successor_parent = min_successor;

        min_successor = min_successor->left;
    };

    struct binary_search_tree min_successor_data = *min_successor;

    min_successor_parent->left = NULL;

    free(min_successor);

    return min_successor_data;
};

struct binary_search_tree binary_search_tree_splice_out_left(struct binary_search_tree* tree)
{
    struct binary_search_tree* left = tree->left;
    struct binary_search_tree left_data = *left;

    tree->left = tree->left->left;

    free(left);

    return left_data;
};

struct binary_search_tree binary_search_tree_splice_out_right(struct binary_search_tree* tree)
{
    struct binary_search_tree* right = tree->right;
    struct binary_search_tree right_data = *right;

    tree->right = tree->right->right;

    free(right);

    return right_data;
};

char* binary_search_tree_remove(struct binary_search_tree* tree, const int key)
{
    if (tree == NULL)
    {
        printf("Cannot remove from uninitialized binary search tree");
        exit(1);
    };

    if (tree->key != key) return binary_search_tree_remove(key > tree->key ? tree->right : tree->left, key);
    
    char* value = tree->value;
    
    struct binary_search_tree replacement_data;

    if (binary_search_tree_has_max_predecessor(tree)) replacement_data = binary_search_tree_remove_max_predecessor(tree);

    else if (binary_search_tree_has_min_successor(tree)) replacement_data = binary_search_tree_remove_min_successor(tree);

    else if (tree->left != NULL) replacement_data = binary_search_tree_splice_out_left(tree);

    else if (tree->right != NULL) replacement_data = binary_search_tree_splice_out_right(tree);

    else {
        cleanup_binary_search_tree(tree);

        return value;
    };

    tree->key = replacement_data.key;
    tree->value = replacement_data.value;

    return value;
};

void binary_search_tree_inorder_print(const struct binary_search_tree* tree)
{
    if (tree == NULL) return;

    binary_search_tree_inorder_print(tree->left);

    printf("Key %i: Value: %s\n", tree->key, tree->value);

    binary_search_tree_inorder_print(tree->right);
};