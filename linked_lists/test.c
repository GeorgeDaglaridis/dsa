#include <stdio.h>
#include <stdlib.h>

// Represents each node of the linked list
typedef struct node {
    int data;
    struct node *next_node;
} node_s;

// List container: Manages the list that manages nodes
typedef struct list {
    node_s *head;
    node_s *tail;
    size_t size;
} list_s;
// cmp(cur->data, key)

int compare_int(const void *a, const void *b) {
    return *(const int *)a - *(const int *)b;
}

int main(void) {

    node_s *n = calloc(1, sizeof(*n));

    n->data = 10;
    n->next_node = NULL;

    int key = 20;

    if( compare_int(&n->data, &key) == 0) {
        printf("There is a match!\n");
    }
    else {
        printf("There is no match!\n");
    }
    free(n);

    return EXIT_SUCCESS;
}