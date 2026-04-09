#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int init(int data);
int add_in_the_beginning(int data);
int add_at_the_end(int data);
void traverse(void);
int exists(int data);

typedef struct node {
    int data;
    struct node *next;

} node_s;

node_s *__head = NULL;

int main(void) {
    // printf("sizeof(\"George\") = %ld\n", sizeof("George"));
    // char arr[40] = "George";
    // printf("sizeof(arr) = %ld\n", sizeof(arr));

    // int (*func_ptr)(int) = add_in_the_beginning;
    int (*func_ptr)(int) = add_at_the_end;

    init(100);

    func_ptr(101);
    func_ptr(102);
    func_ptr(103);

    printf("\nDoes 101 exist ? : %d\n", exists(101));
    printf("Does 102 exist ? : %d\n", exists(102));
    printf("Does 104 exist ? : %d\n", exists(104));
    printf("Does 105 exist ? : %d\n", exists(105));

    //traverse();

    return 0;
}

int init(int data) {
    if(__head) {
        printf("Linked list already initialized!\n");
        return -1;
    }

    // sizeof(node_s) = 48 in case struct has char data[40]
    
    /* 
     * sizeof(node_s) = 16 in case struct has int data
     * struct node* is 8 bytes (64-bit machine) and has to start from a multiple of 8 
     * due to alignement. So it has to start from 8th byte.
     * Hence, 4 bytes for int: 0-1-2-3 + 4 bytes for padding: 4-5-6-7 since struct node* has to start 
     * from a multiple of 8 + 8 bytes for struct node* itself
     */
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
    __head->data = data;
    //memcpy(__head->data, data, strlen(data));
    
    printf("__head->data = %d\n", __head->data);
    printf("address of __head = %p\n", &__head);
    printf("pointer __head points to = %p\n", __head);
    printf("address of __head->data = %p\n", &__head->data);


    //free(__head);
    return 0;
}

int add_in_the_beginning(int data) {
    if(!data) {
        printf("Invalid data!\n");
        return -1;
    }

    printf("\n");

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

    n->data = data;
    //memcpy(n->data, data, strlen(data));
    printf("n->data = %d\n", n->data);

    __head = n;
    printf("address new __head points to: %p\n", __head);
    
    return 0;
}

int add_at_the_end(int data) {
    if(!data) {
        printf("Invalid data!\n");
        return -1;
    }

    printf("\n");

    node_s *n = (node_s *) malloc(sizeof(node_s));
    if(!n) {
        printf("New node memory allocation failed!\n");
        return -2;
    }

    printf("address new node n points to: %p\n", n);
    printf("address of n->data: %p\n", &n->data);

    n->next = NULL;
    n->data = data;
    //memcpy(n->data, data, strlen(data));
    printf("n->data = %d\n", n->data);

    // Link the new node with the previous one.
    // Search untill node->next points to NULL and only then connect it
    // with the newlly created node.
    node_s *cursor;
    for(cursor = __head; cursor->next != NULL; cursor = cursor->next) {
        // printf("address cursor points to: %p\n", cursor);
        // printf("address cursor->next points to: %p\n", cursor->next);

        /* Nothing to do, just heading to the end of the linke list */
    }
    // printf("out of for loop, address cursor points to: %p\n", cursor);
    // printf("out of for loop, address cursor->next points to: %p\n", cursor->next);
    // printf("out of for loop, address __head->next points to: %p\n", __head->next);

    cursor->next = n;

    return 0;
}

void traverse(void) {
    printf("\n");

    int i = 0;
    for(node_s *cursor = __head; cursor != NULL; cursor = cursor->next) {
        // According to the current strategy we have followed
        // for adding new nodes, the last added node is printed
        // first
        printf("Node[%d]: %d\n", i, cursor->data);
        i++;
    }
}

int exists(int data) {
    // 1: true, 0: false
    for(node_s *cursor = __head; cursor != NULL; cursor = cursor->next) {
        if(cursor->data == data) {
            return 1;
        }
    }

    return 0;
}