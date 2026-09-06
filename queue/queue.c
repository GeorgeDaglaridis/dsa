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
    printf("Queue creation:: address: %p, q->head: %p, q->tail: %p, q->size: %u\n", q, q->head, q->tail, q->size);

    return q;
}
