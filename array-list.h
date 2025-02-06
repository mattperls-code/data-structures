#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

struct array_list
{
    int* data;
    int size;
    int capacity;
};

void init_array_list(struct array_list* list, const int initial_capacity);

void cleanup_array_list(struct array_list* list);

void resize_array_list(struct array_list* list, const int new_capacity);

int array_list_get(const struct array_list* list, const int index);

void array_list_push(struct array_list* list, const int value);

int array_list_pop(struct array_list* list);

void array_list_add(struct array_list* list, const int value, const int index);

int array_list_remove(struct array_list* list, const int index);

#endif