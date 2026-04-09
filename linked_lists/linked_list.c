#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int init(char *data);

typedef struct node {
    char data[40];
    struct node *next;

} node_s;


node_s *__head = NULL;

int main(void) {
    // printf("sizeof(\"George\") = %ld\n", sizeof("George"));
    // char arr[40] = "George";
    // printf("sizeof(arr) = %ld\n", sizeof(arr));

    init("George");
    init("Panos");

    return 0;
}

int init(char *data) {
    if(__head) {
        printf("Initialization has happened!\n");
        return -2;
    }

    printf("sizeof(node_s) = %ld\n", sizeof(node_s));

    __head = (node_s *) malloc(sizeof(node_s));
    if(!__head) {
        printf("Memory allocation failed!\n");
        return -1;
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


    free(__head);
    return 0;
}