#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct linked_list
{
    int data;
    struct linked_list* next;
};

void init_linked_list(struct linked_list** list, const int data);

void cleanup_linked_list(struct linked_list* list);

int linked_list_size(const struct linked_list* ist);

int linked_list_get(const struct linked_list* list, const int index);

void linked_list_push(struct linked_list* list, const int value);

int linked_list_pop(struct linked_list* list);

void linked_list_add(struct linked_list* list, const int value, const int index);

int linked_list_remove(struct linked_list* list, const int index);

#endif