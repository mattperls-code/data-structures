#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash-map.h"

static const float MAXIMUM_LOAD_FACTOR = 0.75;
static const int DEFAULT_RESIZE_CAPACITY = 16;
static const int CAPACITY_RESIZE_FACTOR = 2;

void init_hash_map(struct hash_map* map, const int initial_capacity)
{
    if (initial_capacity < 0)
    {
        printf("Hash map capacity must be positive");
        exit(1);
    };

    map->buckets = (struct key_value_pair**) malloc(initial_capacity * sizeof(struct key_value_pair*));

    if (map->buckets == NULL)
    {
        printf("Failed to allocate hash map");
        exit(1);
    };

    map->capacity = initial_capacity;

    for (int i = 0;i<map->capacity;i++)
    {
        map->buckets[i] = NULL;
    };
};

void cleanup_hash_map(struct hash_map* map)
{
    for (int i = 0;i<map->capacity;i++)
    {
        struct key_value_pair* current_entry = map->buckets[i];

        while (current_entry != NULL)
        {
            struct key_value_pair* next_entry = current_entry->next;

            free(current_entry);

            current_entry = next_entry;
        };
    };

    free(map->buckets);
};

int compute_rolling_hash(const char* str, const int max)
{
    int hash = 0;

    for (int i = 0;i<(int) strlen(str);i++)
    {
        hash *= 23;
        hash += str[i];
    };

    return hash % max;
};

float hash_map_load_factor(struct hash_map* map)
{
    int entry_count = 0;

    for (int i = 0;i<map->capacity;i++)
    {
        struct key_value_pair* current_entry = map->buckets[i];

        while (current_entry != NULL)
        {
            entry_count++;

            current_entry = current_entry->next;
        };
    };

    return (float) entry_count / (float) map->capacity;
};

void resize_hash_map(struct hash_map* map, const int new_capacity)
{
    return;

    printf("Resized to capacity of %i\n", new_capacity);

    struct hash_map new_map;

    init_hash_map(&new_map, new_capacity);

    for (int i = 0;i<map->capacity;i++)
    {
        struct key_value_pair* current_entry = map->buckets[i];

        while (current_entry != NULL)
        {
            hash_map_set(&new_map, current_entry->key, current_entry->value);

            current_entry = current_entry->next;
        };
    };
    
    cleanup_hash_map(map);

    *map = new_map;
};

bool hash_map_has(const struct hash_map* map, const char* key)
{
    int bucket_index = compute_rolling_hash(key, map->capacity);

    struct key_value_pair* current_entry = map->buckets[bucket_index];

    while (current_entry != NULL)
    {
        if (strcmp(key, current_entry->key) == 0) return true;

        else current_entry = current_entry->next;
    };

    return false;
};

int hash_map_get(const struct hash_map* map, const char* key)
{
    int bucket_index = compute_rolling_hash(key, map->capacity);

    struct key_value_pair* current_entry = map->buckets[bucket_index];

    while (current_entry != NULL)
    {
        if (strcmp(key, current_entry->key) == 0) return current_entry->value;

        else current_entry = current_entry->next;
    };
    
    printf("Could not find key on hash map get");
    exit(1);
};

void hash_map_set(struct hash_map* map, const char* key, const int value)
{
    if (map->capacity == 0) resize_hash_map(map, DEFAULT_RESIZE_CAPACITY);

    else if (hash_map_load_factor(map) > MAXIMUM_LOAD_FACTOR) resize_hash_map(map, CAPACITY_RESIZE_FACTOR * map->capacity);

    int bucket_index = compute_rolling_hash(key, map->capacity);

    struct key_value_pair** current_entry_ptr = &map->buckets[bucket_index];
    
    while(*current_entry_ptr != NULL)
    {
        if (strcmp(key, (*current_entry_ptr)->key) == 0)
        {
            (*current_entry_ptr)->value = value;

            return;
        }

        else current_entry_ptr = &(*current_entry_ptr)->next;
    };

    *current_entry_ptr = (struct key_value_pair*) malloc(sizeof(struct key_value_pair));

    (*current_entry_ptr)->key = key;
    (*current_entry_ptr)->value = value;
    (*current_entry_ptr)->next = NULL;
};

int hash_map_remove(struct hash_map* map, const char* key)
{
    int bucket_index = compute_rolling_hash(key, map->capacity);

    struct key_value_pair* last_entry = NULL;
    struct key_value_pair* current_entry = map->buckets[bucket_index];

    while(current_entry != NULL)
    {
        if (strcmp(key, current_entry->key) == 0)
        {
            if (last_entry == NULL) map->buckets[bucket_index] = current_entry->next;
            
            else last_entry->next = current_entry->next;

            int value = current_entry->value;

            free(current_entry);

            return value;
        }
        else {
            last_entry = current_entry;
            current_entry = current_entry->next;
        };
    };

    printf("Could not find key on hash map remove");
    exit(1);
};