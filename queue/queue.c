#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Handle to a single queue node (internal to queue_s).
 * 
 * node_s is an implementation detail of queue_s and is not part of the public API:
 * no function in this header accepts or returns a node_s*.
 */
typedef struct node {
    int data;
    struct node *next_node;
} node_s;

// Queue container: Manages the list that manages nodes
struct queue {
    struct node *head;
    struct node *tail;
    unsigned int size;
};

// Helper functions
static void print_queue_details(const queue_s *q) {
    DEBUG_PRINT("Queue details:: address: %p, q->head: %p, q->tail: %p, q->size: %u \n", q, q->head, q->tail, q->size);
}

static void print_nodes(const node_s *n, const size_t node_index, const int node_data, const char *msg) {
    printf("%s[%ld] = %d at address %p\n", msg, node_index, node_data, n);  
}

queue_s *queue_create() {
    queue_s *q = calloc(1, sizeof(*q));
    if(!q) {
        return NULL;
    }
    printf("Queue creation // ");
    print_queue_details(q);

    return q;
}

int queue_enqueue(queue_s **q, int data) {
    // Wrong argument or Queue never created
    if((q == NULL)  || (*q == NULL)) {
      return QUEUE_ERR_INVALID_ARG;  
    }

    node_s *n = malloc(sizeof(*n));
    if(!n) {
        return QUEUE_ERR_ALLOC;
    }
    n->next_node = NULL; // use malloc to explicitly set next_node to NULL or calloc which does it automatically
    n->data = data;

    const char *msg = "Enqueue New Node";
    if((*q)->head == NULL) {
        msg = "Enqueue Init Node";
        (*q)->head = n;
        (*q)->tail = n;
    }
    else {
        // Connect to the old pointer
        (*q)->tail->next_node = n;
        // Update tail pointer
        (*q)->tail = n;
    }      
    (*q)->size++;

    print_queue_details(*q);
    print_nodes(n, (*q)->size, n->data, msg);
    // printf("%s %u: at address %p with data = %d\n", msg, (*q)->size, n, n->data);
        
    return QUEUE_OK;
}

int queue_traverse(const queue_s *q) {
    if(q == NULL){
        return QUEUE_ERR_INVALID_ARG;
    }
    print_queue_details(q);
    
    size_t count = 0;
    for(const node_s *cursor = q->head; cursor != NULL; cursor = cursor->next_node) {
        print_nodes(cursor, count++, cursor->data, "Node");
    }

    return QUEUE_OK;
}
