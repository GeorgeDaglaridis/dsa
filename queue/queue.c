#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

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
    printf("Queue details:: address: %p, q->head: %p, q->tail: %p, q->size: %u \n", q, q->head, q->tail, q->size);
}

static void print_nodes(const node_s *n, const size_t node_index, const int node_data, const char *msg) {
    DEBUG_PRINT("%s[%ld] = %d at address %p\n", msg, node_index, node_data, n);
}

static bool is_queue_empty(const queue_s* q) {
    if((q->head == NULL) && (q->tail == NULL)) {
        return true;
    }
    return false;
}

queue_status queue_create(queue_s **q) {
    if(q == NULL) {
        return QUEUE_ERR_INVALID_ARG;
    }

    *q = calloc(1, sizeof(**q));
    if(!*q) {
        return QUEUE_ERR_ALLOC;
    }
    printf("Queue creation // ");
    print_queue_details(*q);

    //is_queue_empty(q) ? printf("Queue is empty!\n") : printf("Queue is not empty!\n");

    return QUEUE_OK;
}

queue_status queue_destroy(queue_s **q) {
    // Wrong argument or Queue never created
    if((q == NULL)  || (*q == NULL)) {
      return QUEUE_ERR_INVALID_ARG;  
    }

    // Free each node first: memory deallocation
    node_s *cursor = (*q)->head;
    while(cursor != NULL) {
        node_s *temp_next_node = cursor->next_node;

        DEBUG_PRINT("Before freeing: address node cursor points to: %p\n", cursor);
        free(cursor); 
        cursor = temp_next_node;
    }

    // Queue container memory deallocation
    free(*q);
    *q = NULL;

    return QUEUE_OK;
}

queue_status queue_enqueue(queue_s **q, int data) {
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
    
    print_nodes(n, (*q)->size, n->data, msg);
    (*q)->size++;
    print_queue_details(*q);
    // printf("%s %u: at address %p with data = %d\n", msg, (*q)->size, n, n->data);
        
    return QUEUE_OK;
}

queue_status queue_dequeue(queue_s **q, int *out_data) {

    if((q == NULL)  || (*q == NULL) || (out_data == NULL)) {
      return QUEUE_ERR_INVALID_ARG;  
    }
    if(is_queue_empty(*q)) {
        return QUEUE_EMPTY;
    }

    node_s *current = (*q)->head;
    (*q)->head = current->next_node;

    // In case both head and tail point to the last
    // node, both of them will be pointing to NULL
    // after this last node is removed!
    if(current == (*q)->tail) {
        (*q)->tail = current->next_node; // NULL
    }
    // Store the dequeued value.
    *out_data = current->data;
    
    (*q)->size--;

    free(current);
    //current = NULL; redundand since current is local var and goes out of scope on return

    return QUEUE_OK;
}

queue_status queue_traverse(const queue_s *q) {
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

queue_status queue_front(const queue_s *q, int *out_data) {
    if( (q == NULL) || (out_data == NULL) ) {
        return QUEUE_ERR_INVALID_ARG;
    }
    if(is_queue_empty(q)) {
        return QUEUE_EMPTY;
    }
    *out_data = q->head->data;

    return QUEUE_OK;
}

queue_status queue_size(const queue_s *q, size_t *out_size) {
    if( (q == NULL) || (out_size == NULL) ) {
        return QUEUE_ERR_INVALID_ARG;
    }
    *out_size = q->size;

    return QUEUE_OK;
}

const char *queue_status_str(queue_status status) {
    switch (status) {
        case QUEUE_OK: return "QUEUE_OK";
        case QUEUE_ERR_ALLOC: return "Memory allocation failed!";
        case QUEUE_ERR_INVALID_ARG: return "NULL: Invalid argument provided!";
        case QUEUE_EMPTY: return "Container queue is empty!";
        default: return "Unknown error!";
    }
}
