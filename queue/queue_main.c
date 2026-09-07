#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    
    queue_s *q1 = queue_create();
    if(!q1) {
        fprintf(stderr, "Queue memory allocation failed!\n");
        return EXIT_FAILURE;
    }

    printf("\n");
    queue_enqueue(&q1, 10);
    queue_enqueue(&q1, 20);
    queue_enqueue(&q1, 30);
    queue_enqueue(&q1, 40);
    printf("\n");
    queue_traverse(q1);

    int dequeued_value = 0;
    if(queue_dequeue(&q1, &dequeued_value) == QUEUE_OK) {
        printf("\nDequeued value is: %d\n", dequeued_value);
    }
    queue_traverse(q1);

    if(queue_dequeue(&q1, &dequeued_value) == QUEUE_OK) {
        printf("\nDequeued value is: %d\n", dequeued_value);
    }
    queue_traverse(q1);

    if(queue_dequeue(&q1, &dequeued_value) == QUEUE_OK) {
        printf("\nDequeued value is: %d\n", dequeued_value);
    }
    queue_traverse(q1);

    if(queue_dequeue(&q1, &dequeued_value) == QUEUE_OK) {
        printf("\nDequeued value is: %d\n", dequeued_value);
    }
    queue_traverse(q1);

    if(queue_dequeue(&q1, &dequeued_value) == QUEUE_OK) {
        printf("\nDequeued value is: %d\n", dequeued_value);
    }


    free(q1);
    q1=NULL;    
    
    return EXIT_SUCCESS;
}