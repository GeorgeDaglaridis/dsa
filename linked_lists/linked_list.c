#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS    0
#define ERR_ALLOC -1
#define INV_DATA  -2
#define ALRD_INIT -3
#define EMPTY_LL  -4

// Not needed in this code but I added it 
// just for practicing it
#define DEBUG 1

#if DEBUG
    #define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...)
#endif

int list_init(int data);
int add_in_the_beginning(int data);
int add_at_the_end(int data);
int traverse(void);
int exists(int data);
int delete(int data);
int delete_piyush(int data);
int insert(int key, int data);
int insert_piyush(int key, int data);

typedef struct node {
    int data;
    struct node *next_node;

} node_s;

node_s *__head = NULL;

int main(void) {
    // printf("sizeof(\"George\") = %ld\n", sizeof("George"));
    // char arr[40] = "George";
    // printf("sizeof(arr) = %ld\n", sizeof(arr));

    // int (*func_ptr)(int) = add_in_the_beginning;
    int (*func_ptr)(int) = add_at_the_end;

    list_init(100);

    func_ptr(101);
    func_ptr(102);
    func_ptr(103);
    traverse();

    printf("\nDoes 100 exist ? : %d\n", exists(100));
    printf("Does 101 exist ? : %d\n", exists(101));
    printf("Does 102 exist ? : %d\n", exists(102));
    printf("Does 103 exist ? : %d\n", exists(103));
    printf("Does 104 exist ? : %d\n", exists(104));
    printf("Does 105 exist ? : %d\n", exists(105));

    //delete(100);
    //printf("\nDoes 100 exist ? : %d\n", exists(100));
    
    /*
    delete(101);
    printf("Does 101 exist ? : %d\n", exists(101));
    delete(102);
    printf("Does 102 exist ? : %d\n", exists(102));
    delete(100);
    printf("Does 100 exist ? : %d\n", exists(100));
    */

    //delete(103);
    //printf("\nDoes 103 exist ? : %d\n", exists(103));

    insert(102, 50);
    printf("Does 50 exist ? : %d\n", exists(50));
    insert(103, 104);
    printf("Does 104 exist ? : %d\n", exists(104));
    insert(50, 51);
    printf("Does 51 exist ? : %d\n", exists(51));

    insert(106, 55);
    printf("Does 55 exist ? : %d\n", exists(55));


    traverse();

    return SUCCESS;
}

int list_init(int data) {
    if(__head) {
        printf("Linked list already initialized!\n");
        return ALRD_INIT;
    }

    // sizeof(node_s) = 48 in case struct has char data[40]
    
    /* 
     * sizeof(node_s) = 16 in case struct has int data
     * struct node* is 8 bytes (64-bit machine) and has to start from a multiple of 8 
     * due to alignement. So it has to start from 8th byte.
     * Hence, 4 bytes for int: 0-1-2-3 + 4 bytes for padding: 4-5-6-7 since struct node* has to start 
     * from a multiple of 8 + 8 bytes for struct node* itself
     */
    DEBUG_PRINT("sizeof(node_s) = %ld\n", sizeof(node_s));

    __head = (node_s *) malloc(sizeof(node_s));
    if(!__head) {
        printf("Init memory allocation failed!\n");
        return ERR_ALLOC;
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

    __head->next_node = NULL;
    __head->data = data;
    //memcpy(__head->data, data, strlen(data));
    
    DEBUG_PRINT("__head->data = %d\n", __head->data);
    DEBUG_PRINT("address of __head = %p\n", &__head);
    DEBUG_PRINT("pointer __head points to = %p\n", __head);
    DEBUG_PRINT("address of __head->data = %p\n", &__head->data);


    //free(__head);
    return SUCCESS;
}

int add_in_the_beginning(int data) {
    // Cannot add nodes if you have not initialized first!
    if(!__head) {
        printf("Linked list not initialized!\n");
        return EMPTY_LL;
    }

    // 0 is not accepted !
    if(!data) {
        printf("Invalid data!\n");
        return INV_DATA;
    }

    printf("\n");

    node_s *n = (node_s *) malloc(sizeof(node_s));
    if(!n) {
        printf("New node memory allocation failed!\n");
        return ERR_ALLOC;
    }

    DEBUG_PRINT("address new node n points to: %p\n", n);
    DEBUG_PRINT("address of n->data: %p\n", &n->data);
    
    // Link the new node with the previous one.
    // Practically put the new node before the one you
    // created before.
    n->next_node = __head;
    DEBUG_PRINT("address n->next_node points to: %p\n", n->next_node);

    n->data = data;
    //memcpy(n->data, data, strlen(data));
    DEBUG_PRINT("n->data = %d\n", n->data);

    __head = n;
    DEBUG_PRINT("address new __head points to: %p\n", __head);
    
    return SUCCESS;
}

int add_at_the_end(int data) {
    // Cannot add nodes if you have not initialized first!
    if(!__head) {
        printf("Linked list not initialized!\n");
        return EMPTY_LL;
    }

    // 0 is not accepted !
    if(!data) {
        printf("Invalid data!\n");
        return INV_DATA;
    }

    DEBUG_PRINT("\n");

    node_s *n = (node_s *) malloc(sizeof(node_s));
    if(!n) {
        printf("New node memory allocation failed!\n");
        return ERR_ALLOC;
    }

    DEBUG_PRINT("address new node n points to: %p\n", n);
    DEBUG_PRINT("address of n->data: %p\n", &n->data);

    n->next_node = NULL;
    n->data = data;
    //memcpy(n->data, data, strlen(data));
    DEBUG_PRINT("n->data = %d\n", n->data);

    // Link the new node with the previous one.
    // Search untill node->next_node points to NULL and only then connect it
    // with the newlly created node.
    node_s *cursor;
    for(cursor = __head; cursor->next_node != NULL; cursor = cursor->next_node) {
        // printf("address cursor points to: %p\n", cursor);
        // printf("address cursor->next_node points to: %p\n", cursor->next_node);

        /* Nothing to do, just heading to the end of the linke list */
    }
    // printf("out of for loop, address cursor points to: %p\n", cursor);
    // printf("out of for loop, address cursor->next_node points to: %p\n", cursor->next_node);
    // printf("out of for loop, address __head->next_node points to: %p\n", __head->next_node);

    cursor->next_node = n;

    return SUCCESS;
}

int traverse(void) {
    if(!__head) {
        printf("List is empty!\n");
        return EMPTY_LL;
    }

    printf("\n");

    int i = 0;
    for(const node_s *cursor = __head; cursor != NULL; cursor = cursor->next_node) {
        // If you add nodes before the init node (func: add_in_the_beginning) 
        // the last added node is printed first
        // If you add nodes after the init node (func: add_at_the_end) - current strategy- 
        // the last added node is printed last
        printf("Node[%d]: %d\n", i, cursor->data);
        i++;
    }

    return SUCCESS;
}

int exists(int data) {
    // 1: true, 0: false
    for(node_s *cursor = __head; cursor != NULL; cursor = cursor->next_node) {
        if(cursor->data == data) {
            return 1;
        }
    }

    return SUCCESS;
}

int delete(int data) {
    printf("\n");

    node_s *prev_cursor = NULL;

    for(node_s *cursor = __head; cursor != NULL; cursor = cursor->next_node) {
        if(cursor->data == data) {

            char * msg = "Node";
            // Is it ok to delete the very fist node in a linked list ??
            if(cursor == __head) {
                __head = cursor->next_node;
                cursor->next_node = NULL;
                msg = "Init node";
            } else { // Takes into consideration the deletion of the very last node as well
                // Link the previous node with the next_node node
                // from the currently deleted one
                prev_cursor->next_node = cursor->next_node;
                cursor->next_node = NULL;
            }
            printf("%s containing %d at address %p was just deleted\n", msg, cursor->data, cursor);
            free(cursor);
            return 1;

        } else {
            // Save the cursor for every missed data.
            prev_cursor = cursor;
        }
    }

    return SUCCESS;
}

// Delete function according to how piyush implemented it.
// Have not checked it!!!
// I am not sure it takes into consideration the deletion of the 
// very first node of the linked list, nor that it is actuall needed
// or have to be deleted.
int delete_piyush(int data) {
    for(node_s *p = NULL, *c = __head;
                c != NULL;
                p = c, c = c->next_node) {

        if(c->data == data) {
            p->next_node = c->next_node;
            free(c);
            printf("deleted: %d\n", data);
            return 1;
        }    
    }

    return SUCCESS;
}

int insert(int key, int data) {
    printf("\n");

    for(node_s *cursor = __head; cursor != NULL; cursor = cursor->next_node) {
        if(cursor->data == key) {
            node_s *n = (node_s *) malloc(sizeof(node_s));
            if(!n) {
                printf("New node memory allocation failed!\n");
                return ERR_ALLOC;
            }

            n->data = data;
            n->next_node = cursor->next_node;
            cursor->next_node = n;

            DEBUG_PRINT("New node was inserted at address %p ", n);
            DEBUG_PRINT("next to node with address %p\n", cursor);
            DEBUG_PRINT("New node data: %d\n", n->data);

            return 1;
        }
    }
    DEBUG_PRINT("key %d was not found!\n", key);

    return SUCCESS;
}

int insert_piyush(int key, int data) {
    printf("\n");

    node_s *k, *n;

    for(k = __head; k != NULL; k = k->next_node) {
        if(k->data = key) {
            break;
        }
    }

    if(!k) {
        printf("Insertion failed: Key was not found!\n");
        return -4;
    }

    n = (node_s *) malloc(sizeof(node_s));
    if(!n) {
        printf("Insertion failed: New node memory allocation failed!\n");
        return ERR_ALLOC;
    }

    n->data = data;
    n->next_node = k->next_node;
    k->next_node = n;

    DEBUG_PRINT("New node was inserted at address %p ", n);
    DEBUG_PRINT("next to node with address %p\n", k);
    DEBUG_PRINT("New node data: %d\n", n->data);

    return SUCCESS;
}