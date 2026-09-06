#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    
    queue_s *q1 = queue_create();
    if(!q1) {
        fprintf(stderr, "Queue memory allocation failed!\n");
        return EXIT_FAILURE;
    }

    enqueue(&q1, 10);
    enqueue(&q1, 20);
    enqueue(&q1, 30);

    free(q1);
    q1=NULL;    
    
    return EXIT_SUCCESS;
}