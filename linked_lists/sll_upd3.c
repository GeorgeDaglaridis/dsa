#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    LIST_OK = 0,
    LIST_EMPTY = -1,
    LIST_ALRD_INIT = -2,
    LIST_ERR_ALLOC = -3,
    LIST_INV_DATA = -4,
    LIST_KEY_NOT_FOUND = -5
} list_status;

// Represents each node of the linked list
typedef struct node {
    int data;
    struct node *next_node;
} node_s;

// Manages the list that manages nodes
typedef struct list {
    node_s *head;
    node_s *tail;
    size_t size;
} list_s;

int main() {
    return 0;
}