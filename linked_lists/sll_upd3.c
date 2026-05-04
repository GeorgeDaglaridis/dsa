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
    SUCCESS = 0,
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
    DEBUG_PRINT("List creation: ll->head: %p, ll->tail: %p, ll->size: %ld\n", ll->head, ll->tail, ll->size);
    // DEBUG_PRINT("ll points to %p\n", ll);
    // DEBUG_PRINT("address of ll->head %p\n", &(ll->head));
    // DEBUG_PRINT("address of ll->tail %p\n", &(ll->tail));
    // DEBUG_PRINT("address of ll->size %p\n", &(ll->size));

    return ll;
}

// Make sure you free all nodes first before you free
// the list container
list_status list_destroy(list_s **ll) {
    // Defensive check: Do not trust the arguments 
    // user provides you. Check for all cases.
    if( (ll == NULL) || (*ll == NULL) ) {
        return LIST_NOT_FREED;
    }
    else {
        // Free each node first ...
        node_s *cursor = (*ll)->head;
        while(cursor != NULL) {

            node_s *temp_next_node = cursor->next_node;
            DEBUG_PRINT("Before freeing: address node cursor points to: %p\n", cursor);
            free(cursor);
            DEBUG_PRINT("After freeing: address node cursor points to: %p\n", cursor);
            cursor = temp_next_node;
        }
        // Restore list to valid empty state
        (*ll)->head = NULL;
        (*ll)->tail = NULL;
        (*ll)->size = 0;
        // Then free the list container
        //DEBUG_PRINT("Before freeing: (*ll)->head: %p, (*ll)->tail: %p, (*ll)->size: %ld\n", (*ll)->head, (*ll)->tail, (*ll)->size);
        free(*ll);
        //DEBUG_PRINT("After freeing: (*ll)->head: %p, (*ll)->tail: %p, (*ll)->size: %ld\n", (*ll)->head, (*ll)->tail, (*ll)->size);
        *ll = NULL;
        //DEBUG_PRINT("(*ll)->head: %p, (*ll)->tail: %p, (*ll)->size: %ld\n", (*ll)->head, (*ll)->tail, (*ll)->size);
    }
    return SUCCESS;
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
        ll->tail = n; // Consequently, (*ll)->tail->next_node = NULL;

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

    return SUCCESS;
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

    DEBUG_PRINT("Before freeing: address linked list sll1 points to: %p\n", sll1);
    // The following format is called ternary expression
    (list_destroy(&sll1) == LIST_NOT_FREED) ? printf("List not freed ... !\n") : printf("List freed ... !\n");
    DEBUG_PRINT("After freeing: address linked list sll1 points to: %p\n", sll1);
    
    return 0;
}

