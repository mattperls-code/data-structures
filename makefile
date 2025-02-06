CFLAGS = -Wall -Wextra -Werror -std=c11

array-list-test: array-list-test.c array-list.c
	gcc $(CFLAGS) -o array-list-test array-list.c array-list-test.c

linked-list-test: linked-list-test.c linked-list.c
	gcc $(CFLAGS) -o linked-list-test linked-list.c linked-list-test.c

hash-map-test: hash-map-test.c hash-map.c
	gcc ${CFLAGS} -o hash-map-test hash-map.c hash-map-test.c

binary-search-tree-test: binary-search-tree-test.c binary-search-tree.c
	gcc $(CFLAGS) -o binary-search-tree-test binary-search-tree.c binary-search-tree-test.c

.PHONY: clean
clean:
	rm -rf array-list-test linked-list-test hash-map-test binary-search-tree-test