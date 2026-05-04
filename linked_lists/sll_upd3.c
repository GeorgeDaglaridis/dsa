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
    LIST_NOK = -1,
    LIST_EMPTY = -2,
    LIST_ALRD_INIT = -3,
    LIST_ERR_ALLOC = -4,
    LIST_INV_DATA = -5,
    LIST_KEY_NOT_FOUND = -6,
    LIST_NOT_FREED = -7
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

list_status insert_node(list_s *ll, int data) {

    node_s *n = calloc(1, sizeof(*n));
    if(!n) {
        return LIST_ERR_ALLOC;
    }
    n->next_node = NULL;
    n->data = data;

    char *msg = "Node";

    if(ll->head == NULL) {
        ll->head = n;
        ll->tail = n;
        //(*ll)->tail->next_node = NULL;

        msg = "Init node";
        printf("%s created at address %p with data %d\n", msg, n, n->data);

    } else {
        ll->tail->next_node = n;
        ll->tail = n;

        printf("%s created at address %p with data %d\n", msg, n, n->data);
    }
    ll->size++;

    DEBUG_PRINT("ll->head: %p, ll->tail: %p, ll->tail->next_node: %p\n", ll->head, ll->tail, ll->tail->next_node);

    //(*ll)->tail->next_node = n->next_node;
    //(*ll)->head->next_node = (*ll)->tail;

    return LIST_OK;
}

size_t sll_length(list_s *ll) {
    if(!ll) {
        printf("NULL list!\n");
        return 0;
    }
    return ll->size;
}

void traverse_sll(list_s *ll) {
    printf("Linked list sll1 has %ld nodes \n", sll_length(ll));

    size_t i = 0;
    for(node_s *cursor = ll->head; cursor != NULL; cursor = cursor->next_node) {
        printf("Node[%ld] = %d at address %p\n", i++, cursor->data, cursor);
    }
}

int main(void) {

    list_s *sll1 = list_create();
    if(!sll1) {
        printf("Llist memory allocation failed!\n");
        return LIST_ERR_ALLOC;
    }
    printf("Initial Size of sll1: %ld\n", sll_length(sll1));

    (insert_node(sll1, 10) == LIST_ERR_ALLOC) ? printf("Node memory allocation failed!\n") : printf("");
    (insert_node(sll1, 20) == LIST_ERR_ALLOC) ? printf("Node memory allocation failed!\n") : printf("");
    (insert_node(sll1, 30) == LIST_ERR_ALLOC) ? printf("Node memory allocation failed!\n") : printf("");

    traverse_sll(sll1);

    //sll_length(NULL);

    //printf("Before freeing: address sll1 points to: %p\n", sll1);
    // The following format is called ternary expression
    (list_destroy(&sll1) == LIST_NOT_FREED) ? printf("List not freed ... !\n") : printf("List freed ... !\n");
    //printf("After freeing: address sll1 points to: %p\n", sll1);
    
    return 0;
}

