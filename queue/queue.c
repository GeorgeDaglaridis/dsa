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

void print_queue_details(const queue_s *q) {
    DEBUG_PRINT("Queue details:: q->head: %p, q->tail: %p, q->size: %u \n", q->head, q->tail, q->size);
}

queue_s *queue_create() {
    queue_s *q = calloc(1, sizeof(*q));
    if(!q) {
        return NULL;
    }
    printf("Queue creation at address %p // ", q);
    print_queue_details(q);

    return q;
}

int enqueue(queue_s **q, int data) {
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

    const char *msg = "Enqueue new node";
    if((*q)->head == NULL) {
        msg = "Enqueue init node";
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

    printf("%s %u: at address %p with data = %d\n", msg, (*q)->size, n, n->data);
    print_queue_details(*q);

    return QUEUE_OK;
}
