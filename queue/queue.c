#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

// Represents each node of the queue
struct node {
    int data;
    struct node *next_node;
};

// Queue container: Manages the list that manages nodes
struct queue {
    struct node *head;
    struct node *tail;
    unsigned int size;
};

void print_queue_details(const queue_s *q) {
    DEBUG_PRINT("Queue details:: q->head: %p, q->tail: %p, q->size: %u \n", q->head, q->tail, q->size);
}

/**
 * @brief Allocate and initialize a new, empty queue.
 * 
 * @return Pointer to the newly allocated queue_s with size 0 and
 *         no elements, or NULL if allocation fails.
 * 
 * @note The caller owns the returned queue and is responsible for
 *       eventually releassing it via the matching destroy function
 */
queue_s *queue_create() {
    queue_s *q = calloc(1, sizeof(*q));
    if(!q) {
        return NULL;
    }
    printf("Queue creation at address %p // ", q);
    print_queue_details(q);

    return q;
}

/**
 * @brief Allocate a new node holding @p data and append it to the tail
 *        of the queue.
 * 
 * @param q    Address of the caller's queue pointer. Must not be NULL, and *q
 *             must already point to a queue previously returned by queue_create().
 * @param data Value to store in the new node.
 * 
 * @return QUEUE_ERR_INVALID_ARG if @p q or *q is NULL,
 *         QUEUE_ERR_ALLOC if new node's allocation failed,
 *         QUEUE_OK on success.
 */
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

    printf("%s: at address %p with data = %d\n", msg, n, n->data);
    print_queue_details(*q);

    return QUEUE_OK;
}
