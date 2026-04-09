#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int init(char *data);
int add_in_the_beginning(char *data);
void traverse(void);

typedef struct node {
    char data[40];
    struct node *next;

} node_s;

node_s *__head = NULL;

int main(void) {
    // printf("sizeof(\"George\") = %ld\n", sizeof("George"));
    // char arr[40] = "George";
    // printf("sizeof(arr) = %ld\n", sizeof(arr));

    int (*func_ptr)(char *) = add_in_the_beginning;

    init("George");

    func_ptr("Panos");
    func_ptr("Stella");

    traverse();

    return 0;
}

int init(char *data) {
    if(__head) {
        printf("Linked list already initialized!\n");
        return -1;
    }

    printf("sizeof(node_s) = %ld\n", sizeof(node_s));

    __head = (node_s *) malloc(sizeof(node_s));
    if(!__head) {
        printf("Init memory allocation failed!\n");
        return -2;
    }

    // printf("strlen(data) = %ld\n", strlen(data));
    // // "George" is a string literal
    // // but here, basically, I am asking the size of the pointer itself,
    // // which is 8 bytes on a 64-bit machine.
    // printf("sizeof(data) = %ld\n", sizeof(data));

    // printf("\"George\"[0] = %c\n", "George"[0]);
    // printf("\"George\"[1] = %c\n", "George"[1]);
    // printf("\"George\"[2] = %c\n", "George"[2]);
    // printf("\"George\"[3] = %c\n", "George"[3]);
    // printf("\"George\"[4] = %c\n", "George"[4]);
    // printf("\"George\"[5] = %c\n", "George"[5]);
    // printf("\"George\"[6] = %c\n", "George"[6]);

    __head->next = NULL;
    memcpy(__head->data, data, strlen(data));
    
    printf("__head->data = %s\n", __head->data);
    printf("address of __head = %p\n", &__head);
    printf("pointer __head points to = %p\n", __head);
    printf("address of __head->data = %p\n", &__head->data);


    //free(__head);
    return 0;
}

int add_in_the_beginning(char *data) {
    if(!data) {
        printf("Invalid data!\n");
        return -1;
    }

    printf("\n\n");

    node_s *n = (node_s *) malloc(sizeof(node_s));
    if(!n) {
        printf("New node memory allocation failed!\n");
        return -2;
    }

    printf("address new node n points to: %p\n", n);
    printf("address of n->data: %p\n", &n->data);
    
    // Link the new node with the previous one.
    // Practically put the new node before the one you
    // created before.
    n->next = __head;
    printf("address n->next points to: %p\n", n->next);

    memcpy(n->data, data, strlen(data));
    printf("n->data = %s\n", n->data);

    __head = n;
    printf("address new __head points to: %p\n", __head);
    
    return 0;
}

void traverse(void) {
    printf("\n\n");

    int i = 0;
    for(node_s *cursor = __head; cursor != NULL; cursor = cursor->next) {
        // According to the current strategy we have followed
        // for adding new nodes, the last added node is printed
        // first
        printf("Node[%d]: %s\n", i, cursor->data);
        i++;
    }
}