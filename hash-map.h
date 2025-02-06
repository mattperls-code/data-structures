#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdbool.h>

struct key_value_pair
{
    const char* key;
    int value;
    struct key_value_pair* next;
};

struct hash_map
{
    struct key_value_pair** buckets;
    int capacity;
};

void init_hash_map(struct hash_map* map, const int initial_capacity);

void cleanup_hash_map(struct hash_map* map);

bool hash_map_has(const struct hash_map* map, const char* key);

int hash_map_get(const struct hash_map* map, const char* key);

void hash_map_set(struct hash_map* map, const char* key, const int value);

int hash_map_remove(struct hash_map* map, const char* key);

#endif