#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array-list.h"

static const int DEFAULT_RESIZE_CAPACITY = 16;
static const int CAPACITY_RESIZE_FACTOR = 2;

void init_array_list(struct array_list* list, const int initial_capacity)
{
    if (initial_capacity < 0)
    {
        printf("Array list capacity must be positive");
        exit(1);
    };

    list->data = (int*) malloc(initial_capacity * sizeof(int));

    if (list->data == NULL)
    {
        printf("Failed to allocate array list");
        exit(1);
    };

    list->size = 0;
    list->capacity = initial_capacity;
};

void cleanup_array_list(struct array_list* list)
{
    free(list->data);
};

void resize_array_list(struct array_list* list, const int new_capacity)
{
    if (new_capacity < 0)
    {
        printf("Array list capacity must be positive");
        exit(1);
    };

    list->data = (int*) realloc(list->data, new_capacity * sizeof(int));

    if (list->data == NULL)
    {
        printf("Failed to allocate array list");
        exit(1);
    };

    list->capacity = new_capacity;

    if (list->capacity < list->size) list->size = list->capacity;
};

int array_list_get(const struct array_list* list, const int index)
{
    if (index >= list->size)
    {
        printf("Array list access out of bounds");
        exit(1);
    };

    return list->data[index];
};

void array_list_push(struct array_list* list, const int value)
{
    if (list->capacity == 0) resize_array_list(list, DEFAULT_RESIZE_CAPACITY);

    else if (list->size == list->capacity) resize_array_list(list, list->capacity * CAPACITY_RESIZE_FACTOR);

    list->data[list->size] = value;

    list->size++;
};

int array_list_pop(struct array_list* list)
{
    if (list->size == 0)
    {
        printf("Invalid array list removal index");
        exit(1);
    };

    list->size--;

    return list->data[list->size];
};

void array_list_add(struct array_list* list, const int value, const int index)
{
    if (index < 0 || index > list->size)
    {
        printf("Invalid array list add index");
        exit(1);
    };

    if (index == list->size) array_list_push(list, value);
    else {
        if (list->capacity == 0) resize_array_list(list, DEFAULT_RESIZE_CAPACITY);

        else if (list->size == list->capacity) resize_array_list(list, list->capacity * CAPACITY_RESIZE_FACTOR);
        
        memmove(list->data + index + 1, list->data + index, (list->size - index) * sizeof(int));

        list->data[index] = value;

        list->size++;
    };
};

int array_list_remove(struct array_list* list, const int index)
{
    if (index < 0 || index >= list->size)
    {
        printf("Invalid array list remove index");
        exit(1);
    };

    if (index == list->size - 1) return array_list_pop(list);
    else {
        int value = list->data[index];

        memmove(list->data + index, list->data + index + 1, (list->size - index - 1) * sizeof(int));

        list->size--;

        return value;
    };
};