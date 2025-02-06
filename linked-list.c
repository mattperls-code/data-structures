#include <stdio.h>
#include <stdlib.h>

#include "linked-list.h"

void init_linked_list(struct linked_list** list, const int data)
{
    *list = (struct linked_list*) malloc(sizeof(struct linked_list));

    if (*list == NULL)
    {
        printf("Failed to allocate linked list");
        exit(1);
    };

    (*list)->data = data;
    (*list)->next = NULL;
};

void cleanup_linked_list(struct linked_list* list)
{
    if (list == NULL) return;

    cleanup_linked_list(list->next);

    free(list);
};

int linked_list_size(const struct linked_list* list)
{
    if (list == NULL) return 0;

    return 1 + linked_list_size(list->next);
};

int linked_list_get(const struct linked_list* list, const int index)
{
    if (list == NULL || index < 0)
    {
        printf("Linked list index out of bounds");
        exit(1);
    };

    if (index == 0) return list->data;

    return linked_list_get(list->next, index - 1);
};

void linked_list_push(struct linked_list* list, const int value)
{
    if (list == NULL)
    {
        printf("Cannot push onto uninitialized linked list");
        exit(1);
    };

    struct linked_list* original_head_clone = NULL;

    init_linked_list(&original_head_clone, list->data);
    
    original_head_clone->next = list->next;

    list->data = value;
    list->next = original_head_clone;
};

int linked_list_pop(struct linked_list* list)
{
    if (list == NULL)
    {
        printf("Cannot pop off uninitialized linked list");
        exit(1);
    };
    
    struct linked_list* next = list->next;

    if (next == NULL)
    {
        printf("Cannot pop off linked list root node");
        exit(1);
    };
    
    list->data = next->data;
    list->next = next->next;
    
    int value = next->data;

    free(next);

    return value;
};

void linked_list_add(struct linked_list* list, const int value, const int index)
{
    if (index < 0)
    {
        printf("Illegal index argument to linked list add");
        exit(1);
    };

    if (list == NULL)
    {
        printf("Cannot add to uninitialized linked list");
        exit(1);
    };

    if (index == 0) linked_list_push(list, value);
    else {
        struct linked_list* target_parent = list;

        for (int i = 0;i<index - 1;i++)
        {
            target_parent = target_parent->next;

            if (target_parent == NULL)
            {
                printf("Linked list index out of bound on add");
                exit(1);
            };
        };

        struct linked_list* target = NULL;

        init_linked_list(&target, value);

        struct linked_list* target_child = target_parent->next;

        target->next = target_child;
        target_parent->next = target;
    };
};

int linked_list_remove(struct linked_list* list, const int index)
{
    if (index < 0)
    {
        printf("Illegal index argument to linked list remove");
        exit(1);
    };

    if (list == NULL)
    {
        printf("Cannot remove from uninitialized linked list");
        exit(1);
    };

    if (index == 0) return linked_list_pop(list);
    else {
        struct linked_list* target_parent = list;

        for (int i = 0;i<index - 1;i++)
        {
            target_parent = target_parent->next;

            if (target_parent == NULL)
            {
                printf("Linked list index out of bound on remove");
                exit(1);
            };
        };

        struct linked_list* target = target_parent->next;

        if (target == NULL)
        {
            printf("Linked list index out of bound on remove");
            exit(1);
        };

        struct linked_list* target_child = target->next;

        target_parent->next = target_child;

        int value = target->data;

        free(target);

        return value;
    };
};