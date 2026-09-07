#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

#define CHECK_FATAL(x) do {                                          \
    queue_status status = (x);                                       \
    if(status != QUEUE_OK) {                                         \
        fprintf(stderr, "Fatal: %s\n", queue_status_str(status));    \
        exit(EXIT_FAILURE);                                          \
    }                                                                \
} while(0)

int main(void) {
    
    queue_s *q1 = queue_create();
    if(!q1) {
        fprintf(stderr, "Queue memory allocation failed!\n");
        return EXIT_FAILURE;
    }

    printf("\n");
    CHECK_FATAL(queue_enqueue(&q1, 10));
    CHECK_FATAL(queue_enqueue(&q1, 20));
    CHECK_FATAL(queue_enqueue(&q1, 30));
    CHECK_FATAL(queue_enqueue(&q1, 40));
    printf("\n");

    queue_status status = queue_traverse(q1); 
    if(status != QUEUE_OK) {
        fprintf(stderr, "%s\n", queue_status_str(status));
    }

    int dequeued_value = 0;
    CHECK_FATAL(queue_dequeue(&q1, &dequeued_value));
    printf("\nDequeued value is: %d\n", dequeued_value);

    status = queue_traverse(q1); 
    if(status != QUEUE_OK) {
        fprintf(stderr, "%s\n", queue_status_str(status));
    }

    CHECK_FATAL(queue_dequeue(&q1, &dequeued_value));
    printf("\nDequeued value is: %d\n", dequeued_value);

    status = queue_traverse(q1); 
    if(status != QUEUE_OK) {
        fprintf(stderr, "%s\n", queue_status_str(status));
    }

    CHECK_FATAL(queue_dequeue(&q1, &dequeued_value));
    printf("\nDequeued value is: %d\n", dequeued_value);

    status = queue_traverse(q1); 
    if(status != QUEUE_OK) {
        fprintf(stderr, "%s\n", queue_status_str(status));
    }

    CHECK_FATAL(queue_dequeue(&q1, &dequeued_value));
    printf("\nDequeued value is: %d\n", dequeued_value);

    status = queue_traverse(q1); 
    if(status != QUEUE_OK) {
        fprintf(stderr, "%s\n", queue_status_str(status));
    }

    CHECK_FATAL(queue_dequeue(&q1, &dequeued_value));
    printf("\nDequeued value is: %d\n", dequeued_value);
    
    free(q1);
    q1=NULL;    
    
    return EXIT_SUCCESS;
}