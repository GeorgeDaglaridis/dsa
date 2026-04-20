#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Not needed in this code but I added it 
// just for practicing it
#define DEBUG 1

#if DEBUG
    #define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...)
#endif

typedef enum {
    LIST_OK = 0,
    LIST_EMPTY = -1,
    LIST_ALRD_INIT = -2,
    LIST_ERR_ALLOC = -3,
    LIST_INV_DATA = -4,
    LIST_KEY_NOT_FOUND = -5
} list_status;

typedef struct node {
    int data;
    struct node *next_node;

} node_s;

node_s *__head = NULL;

list_status list_init(int data);
list_status add_in_the_beginning(int data);
list_status add_at_the_end(int data);
size_t ll_lenght(void);
void traverse_ll(void);
list_status reverse(void);
bool list_contains(int data);
bool delete_node(int data);
bool delete_node_piyush(int data);
bool delete_node_piyush_upd(int data);
list_status insert_node_after_key(int key, int data);
list_status insert_node_piyush(int key, int data);

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
    traverse_ll();
    printf("Linked list has %lu nodes\n", ll_lenght());

    printf("\nDoes 100 exist ? : %d\n", list_contains(100));
    printf("Does 101 exist ? : %d\n", list_contains(101));
    printf("Does 102 exist ? : %d\n", list_contains(102));
    printf("Does 103 exist ? : %d\n", list_contains(103));
    printf("Does 104 exist ? : %d\n", list_contains(104));
    printf("Does 105 exist ? : %d\n", list_contains(105));

    //delete_node(100);
    //printf("\nDoes 100 exist ? : %d\n", list_contains(100));
    
    /*
    delete_node(101);
    printf("Does 101 exist ? : %d\n", list_contains(101));
    delete_node(102);
    printf("Does 102 exist ? : %d\n", list_contains(102));
    delete_node(100);
    printf("Does 100 exist ? : %d\n", list_contains(100));
    */

    //delete_node(103);
    //printf("\nDoes 103 exist ? : %d\n", list_contains(103));

    insert_node_after_key(102, 50);
    printf("Does 50 exist ? : %d\n", list_contains(50));
    insert_node_after_key(103, 104);
    printf("Does 104 exist ? : %d\n", list_contains(104));
    insert_node_after_key(50, 51);
    printf("Does 51 exist ? : %d\n", list_contains(51));

    insert_node_after_key(106, 55);
    printf("Does 55 exist ? : %d\n", list_contains(55));

    traverse_ll();
    printf("Linked list has %lu nodes\n", ll_lenght());
    // Reverse
    reverse();
    traverse_ll();
    // Reverse back
    reverse();
    traverse_ll();

    func_ptr(105);
    func_ptr(106);
    func_ptr(107);
    traverse_ll();
    printf("Linked list has %lu nodes\n", ll_lenght());

     // Reverse again
    reverse();
    traverse_ll();
    // Reverse back again
    reverse();
    traverse_ll();

    return 0;
}

list_status list_init(int data) {
    if(__head) {
        printf("Linked list already initialized!\n");
        return LIST_ALRD_INIT;
    }

    // sizeof(node_s) = 48 in case struct has char data[40]
    
    /* 
     * sizeof(node_s) = 16 in case struct has int data
     * struct node* is 8 bytes (64-bit machine) and has to start from a multiple of 8 
     * due to alignement. So it has to start from 8th byte.
     * Hence, 4 bytes for int: 0-1-2-3 + 4 bytes for padding: 4-5-6-7 since struct node* has to start 
     * from a multiple of 8 + 8 bytes for struct node* itself
     */
    DEBUG_PRINT("sizeof(node_s)  = %ld\n", sizeof(node_s));
    DEBUG_PRINT("sizeof(*__head) = %ld\n", sizeof(*__head));
    DEBUG_PRINT("sizeof(__head)  = %ld\n", sizeof(__head));
    
    // sizeof(node_s) = 48 in case struct has char data[40]

    __head = malloc(sizeof(*__head));
    if(!__head) {
        printf("Init memory allocation failed!\n");
        return LIST_ERR_ALLOC;
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
    return LIST_OK;
}

list_status add_in_the_beginning(int data) {
    // Cannot add nodes if you have not initialized first!
    if(!__head) {
        printf("Linked list not initialized!\n");
        return LIST_EMPTY;
    }

    // 0 is not accepted !
    if(!data) {
        printf("Invalid data!\n");
        return LIST_INV_DATA;
    }

    printf("\n");

    node_s *n = malloc(sizeof(*n));
    if(!n) {
        printf("New node memory allocation failed!\n");
        return LIST_ERR_ALLOC;
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
    
    return LIST_OK;
}

list_status add_at_the_end(int data) {
    // Cannot add nodes if you have not initialized first!
    if(!__head) {
        printf("Linked list not initialized!\n");
        return LIST_EMPTY;
    }

    // 0 is not accepted !
    if(!data) {
        printf("Invalid data!\n");
        return LIST_INV_DATA;
    }

    DEBUG_PRINT("\n");

    node_s *n = malloc(sizeof(*n));
    if(!n) {
        printf("New node memory allocation failed!\n");
        return LIST_ERR_ALLOC;
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

    return LIST_OK;
}

size_t ll_lenght(void) {
    size_t i = 0;
    for(const node_s *cursor = __head; 
                      cursor != NULL; 
                      cursor = cursor->next_node) {
        i++;
    }
    return i;
}

void traverse_ll(void) {
    // In this function, checking whether ll is empty is a design choice
    // rather than a necessity.
    // Many APIs simply do nothing for empty lists
    // if(!__head) {
    //     printf("List is empty!\n");
    //     return EMPTY_LL;
    // }

    printf("\n");

    size_t i = 0;
    for(const node_s *cursor = __head; cursor != NULL; cursor = cursor->next_node) {
        // If you add nodes before the init node (func: add_in_the_beginning) 
        // the last added node is printed first
        // If you add nodes after the init node (func: add_at_the_end) - current strategy- 
        // the last added node is printed last
        printf("Node[%lu]: %d\n", i++, cursor->data);
    }
}

list_status reverse(void) {

    // Since we are using VLAs we have to make sure
    // that its size is not 0, thus the linked list
    // is not empty.
    if(!__head) {
        printf("Linked list not initialized!\n");
        return LIST_EMPTY;
    }

    size_t ll_size = ll_lenght();

    node_s *n_arr[ll_size];
    
    // Making sure all elements of VLA are initialized to NULL.
    // Recommended only for VLAs of small length.
    size_t i = 0;
    for(i = 0; i < ll_size; i++) {
        n_arr[i] = NULL;
    }
    i = 0;

    size_t count = 0;
    for(node_s *cursor = __head; 
                cursor != NULL; 
                cursor = cursor->next_node) {

        n_arr[count++] = cursor;
    }

    //__head now points to the last node of the reversed linked list
    __head = n_arr[count-1];
    
    for(i = count - 1; i > 0; i--) {
        n_arr[i]->next_node = n_arr[i-1];
    }
    // The node that was previously pointed by the __head in now the last node in the reversed linked list
    n_arr[i]->next_node = NULL;

    return LIST_OK;
}

bool list_contains(int data) {
    for(const node_s *cursor = __head; cursor != NULL; cursor = cursor->next_node) {
        if(cursor->data == data) {
            return true;
        }
    }
    return false;
}

bool delete_node(int data) {
    printf("\n");

    node_s *prev_cursor = NULL;

    for(node_s *cursor = __head; cursor != NULL; cursor = cursor->next_node) {
        if(cursor->data == data) {

            char * msg = "Node";
            // Is it ok to delete the very fist node in a linked list ?? Yes
            if(cursor == __head) {
                __head = cursor->next_node;

                // Maybe it is more clear this way, but not needed since 
                // you are going to free cursor
                //cursor->next_node = NULL;
                msg = "Init node";
            } else { // Takes into consideration the deletion of the very last node as well
                // Link the previous node with the next_node node
                // from the currently deleted one
                prev_cursor->next_node = cursor->next_node;

                // Maybe it is more clear this way, but not needed since 
                // you are going to free cursor
                //cursor->next_node = NULL;
            }
            printf("%s containing %d at address %p was just deleted\n", msg, cursor->data, cursor);
            free(cursor);
            return true;

        } else {
            // Save the cursor for every missed data.
            prev_cursor = cursor;
        }
    }

    return false;
}

// Delete function according to how piyush implemented it.
// Have not checked it!!!
// I am not sure it takes into consideration the deletion of the 
// very first node of the linked list (I believe it does not), nor 
// that it is actuall needed or have to be deleted.
bool delete_node_piyush(int data) {
    for(node_s *p = NULL, *c = __head;
                c != NULL;
                p = c, c = c->next_node) {

        if(c->data == data) {
            p->next_node = c->next_node;
            free(c);
            printf("deleted: %d\n", data);
            return true;
        }    
    }

    return false;
}

// Not tested but I believe this takes into
// consideration the removal of __head
bool delete_node_piyush_upd(int data) {
    for(node_s *p = NULL, *c = __head;
                c != NULL;
                p = c, c = c->next_node) {

        if(c->data == data) {
            if(c == __head) {
                __head = c->next_node;
            }
            else {
                p->next_node = c->next_node;
            }            
            free(c);
            printf("deleted: %d\n", data);
            return true;
        }    
    }
    return false;
}

list_status insert_node_after_key(int key, int data) {
    if(!__head) {
        printf("List is empty!\n");
        return LIST_EMPTY;
    }

    printf("\n");

    for(node_s *cursor = __head; cursor != NULL; cursor = cursor->next_node) {
        if(cursor->data == key) {
            node_s *n = malloc(sizeof(*n));
            if(!n) {
                printf("New node memory allocation failed!\n");
                return LIST_ERR_ALLOC;
            }

            n->data = data;
            n->next_node = cursor->next_node;
            cursor->next_node = n;

            DEBUG_PRINT("New node was inserted at address %p ", n);
            DEBUG_PRINT("next to node with address %p\n", cursor);
            DEBUG_PRINT("New node data: %d\n", n->data);

            return LIST_OK;
        }
    }
    DEBUG_PRINT("key %d was not found!\n", key);

    return LIST_KEY_NOT_FOUND;
}

// I think I like the way this function is written
// by piuysh more than mine.
list_status insert_node_piyush(int key, int data) {
    printf("\n");

    node_s *k, *n;

    for(k = __head; k != NULL; k = k->next_node) {
        if(k->data == key) {
            break;
        }
    }

    if(!k) {
        printf("Insertion failed: Key was not found!\n");
        return LIST_KEY_NOT_FOUND;
    }

    n = malloc(sizeof(*n));
    if(!n) {
        printf("Insertion failed: New node memory allocation failed!\n");
        return LIST_ERR_ALLOC;
    }

    n->data = data;
    n->next_node = k->next_node;
    k->next_node = n;

    DEBUG_PRINT("New node was inserted at address %p ", n);
    DEBUG_PRINT("next to node with address %p\n", k);
    DEBUG_PRINT("New node data: %d\n", n->data);

    return LIST_OK;
}