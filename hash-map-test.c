#include <stdio.h>

#include "hash-map.h"

int main()
{
    struct hash_map my_map;

    init_hash_map(&my_map, 1);
    
    printf("Has key \"a\": %s\n", hash_map_has(&my_map, "a") ? "true" : "false");
    printf("Has key \"b\": %s\n", hash_map_has(&my_map, "b") ? "true" : "false");
    printf("Has key \"c\": %s\n", hash_map_has(&my_map, "c") ? "true" : "false");

    hash_map_set(&my_map, "a", 10);
    hash_map_set(&my_map, "b", 20);

    printf("Has key \"a\": %s\n", hash_map_has(&my_map, "a") ? "true" : "false");
    printf("Has key \"b\": %s\n", hash_map_has(&my_map, "b") ? "true" : "false");
    printf("Has key \"c\": %s\n", hash_map_has(&my_map, "c") ? "true" : "false");

    printf("Value at key \"a\": %i\n", hash_map_get(&my_map, "a"));
    printf("Value at key \"b\": %i\n", hash_map_get(&my_map, "b"));

    hash_map_set(&my_map, "c", hash_map_get(&my_map, "b") + 10);

    printf("Value at key \"c\": %i\n", hash_map_get(&my_map, "c"));

    hash_map_remove(&my_map, "a");
    hash_map_remove(&my_map, "b");
    hash_map_remove(&my_map, "c");

    printf("Has key \"a\": %s\n", hash_map_has(&my_map, "a") ? "true" : "false");
    printf("Has key \"b\": %s\n", hash_map_has(&my_map, "b") ? "true" : "false");
    printf("Has key \"c\": %s\n", hash_map_has(&my_map, "c") ? "true" : "false");

    return 0;
};