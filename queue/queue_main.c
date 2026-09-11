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
    
    queue_s *q1 = NULL;
    queue_status status = queue_create(&q1);
    if(status != QUEUE_OK) {
        fprintf(stderr, "Queue creation: %s\n", queue_status_str(status));
        return EXIT_FAILURE;
    }

    printf("\n");
    CHECK_FATAL(queue_enqueue(&q1, 10));
    CHECK_FATAL(queue_enqueue(&q1, 20));
    CHECK_FATAL(queue_enqueue(&q1, 30));
    CHECK_FATAL(queue_enqueue(&q1, 40));
    printf("\n");

    // status = queue_traverse(q1); 
    // if(status != QUEUE_OK) {
    //     fprintf(stderr, "%s\n", queue_status_str(status));
    // }
    CHECK_FATAL(queue_traverse(q1));

    int dequeued_value = 0;
    CHECK_FATAL(queue_dequeue(&q1, &dequeued_value));
    printf("\nDequeued value is: %d\n", dequeued_value);

    CHECK_FATAL(queue_traverse(q1));

    dequeued_value = 0;
    CHECK_FATAL(queue_dequeue(&q1, &dequeued_value));
    printf("\nDequeued value is: %d\n", dequeued_value);
    
    CHECK_FATAL(queue_traverse(q1));

    dequeued_value = 0;
    CHECK_FATAL(queue_dequeue(&q1, &dequeued_value));
    printf("\nDequeued value is: %d\n", dequeued_value);
    
    CHECK_FATAL(queue_traverse(q1));

    dequeued_value = 0;
    CHECK_FATAL(queue_dequeue(&q1, &dequeued_value));
    printf("\nDequeued value is: %d\n", dequeued_value);
    
    CHECK_FATAL(queue_traverse(q1));

    // 
    /**
     * "Pushed" to QUEUE_EMPTY
     * 
     * Constructing how return values should be treated is more
     * of caller's design choice.
     * 
     * Function queue_dequeeu should be called as many times as
     * the number of nodes function queue_enqueue has put in.
     * Any QUEUE_EMPTY return value in between calls of the funcion
     * queue_dequeue should be treated as fatal error.
     * 
     * Knowing that all the nodes you have put in have already been
     * consumed and keep calling queue_dequeue is something that
     * should not happen. This is the case I added bellow just to 
     * check if enum QUEUE_EMPTY gets returned and in that case
     * it is handled as a trivial case.
     * 
     * CLAUDE CODE SESSION ID: 439484a3-57f6-4556-9251-853720311f8c
     * 
     */ 
    // dequeued_value = 0;
    // status = queue_dequeue(&q1, &dequeued_value);
    // if(status == QUEUE_OK) {
    //     printf("\nDequeued value is: %d\n", dequeued_value);
    // }
    // else if(status == QUEUE_EMPTY) {
    //     printf("%s\n", queue_status_str(status));
    // }
    // else if(status == QUEUE_ERR_INVALID_ARG) {
    //     fprintf(stderr, "%s\n", queue_status_str(status));
    //     exit(EXIT_FAILURE);
    // }
    // else {
    //     fprintf(stderr, "Unextected status: %d\n", status);
    //     exit(EXIT_FAILURE);
    // }
    
    // Given the particular test run (function calls) above, keep in mind that
    // when flow reaches this point all nodes have already been dequeued
    // and function queue_destroy has only to deallocate the queue container.
    DEBUG_PRINT("Before freeing: address queue points to: %p\n", q1);
    CHECK_FATAL(queue_destroy(&q1));
    DEBUG_PRINT("After freeing: address queue points to: %p\n", q1);
    
    return EXIT_SUCCESS;
}