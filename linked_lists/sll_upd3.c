#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG 1

#if DEBUG
    #define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...)
#endif

typedef enum {
    LIST_OK = 0,
    LIST_EMPTY = -1,
    LIST_ALRD_INIT = -2,
    LIST_ERR_ALLOC = -3,
    LIST_INV_DATA = -4,
    LIST_KEY_NOT_FOUND = -5,
    LIST_NOT_FREED = -6
} list_status;

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

list_s *list_create(void) {
    
    list_s *ll = calloc(1, sizeof(*ll));
    if(!ll) {
        return NULL;
    }

    return ll;
}

// Incomplete: Make sure you free all nodes first before you free
// the list container
list_status list_destroy(list_s **ll) {
    // Defensive check: Do not trust the arguments 
    // user provides you. Check for all cases.
    if (ll == NULL) {
        return LIST_NOT_FREED;
    }
    else if (*ll == NULL) {
        return LIST_NOT_FREED;
    }
    else {
        free(*ll);
        *ll = NULL;
        return 0;
    }
}

size_t ll_length(list_s *ll) {
    return ll->size;
}

int main(void) {

    list_s *sll1 = list_create();
    if(!sll1) {
        printf("Memory allocation failed!\n");
        return LIST_ERR_ALLOC;
    }
    printf("Size of sll1: %ld\n", ll_length(sll1));

    //printf("Before freeing: address sll1 points to: %p\n", sll1);
    // The following format is called ternary expression
    (list_destroy(&sll1) == LIST_NOT_FREED) ? printf("List not freed ... !\n") : printf("List freed ... !\n");
    //printf("After freeing: address sll1 points to: %p\n", sll1);
    
    return 0;
}

