#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// Add a new node always at the end of the linked list
list_status append_node(node_s **sll_head, char *ll_name, int data);
// Insert a new node after a specific key in the linked list
list_status insert_node_after_key(node_s *sll_head, char *ll_name, int key, int data);
// Delete a new node with a specific key from the linked list
bool delete_node(node_s **sll_head, char *ll_name, int data);
// Reverse the whole linked list
list_status reverse(node_s **sll_head);
// Traverse the whole linked list
void traverse_sll(node_s *sll_head, char *ll_name);
// Length of the linked list
size_t ll_lenght(const node_s *sll_head);
// Check if given data exist in the linked list
bool list_contains(const node_s *sll_head, int data);

int main(void) {

    // Create empty single linked list 1 (no elements/nodes yet)
    node_s *__head_sll1 = NULL;

    if( append_node(&__head_sll1, "sll1", 10) == 0 ) {
        printf("Init node added ...\n");
    }
    else {
        exit(1);
    }
    //traverse_sll(__head_sll1, "sll1");

    // We print __head_sll1, we do not iterate over the linked list 1
    //printf("Node at address %p with data %d\n", __head_sll1, __head_sll1->data);
    //__head_sll1->data = 20;
    //printf("Node at address %p with data %d\n", __head_sll1, __head_sll1->data);
    
    if( append_node(&__head_sll1, "sll1", 20) == 0 ) {
        printf("Node added ...\n");
    }
    else {
        exit(1);
    }
    //traverse_sll(__head_sll1);

    if( append_node(&__head_sll1, "sll1", 30) == 0 ) {
        printf("Node added ...\n");
    }
    else {
        exit(1);
    }
    printf("Linked list sll1 has %lu nodes\n", ll_lenght(__head_sll1));
    traverse_sll(__head_sll1, "sll1");
    printf("Does 10 exist ? : %d\n", list_contains(__head_sll1, 10));
    printf("Does 20 exist ? : %d\n", list_contains(__head_sll1, 20));
    printf("Does 30 exist ? : %d\n", list_contains(__head_sll1, 30));
    printf("Does 40 exist ? : %d\n", list_contains(__head_sll1, 40));

    if( insert_node_after_key(__head_sll1, "sll1", 20, 25) != 0 ) {
        exit(1);
    }
    else {
        printf("Node inserted ...\n");
    }

    if( insert_node_after_key(__head_sll1, "sll1", 30, 35) != 0 ) {
        exit(1);
    }
    else {
        printf("Node inserted ...\n");
    }
    printf("Linked list sll1 has %lu nodes\n", ll_lenght(__head_sll1));
    traverse_sll(__head_sll1, "sll1");
    printf("Does 25 exist ? : %d\n", list_contains(__head_sll1, 25));
    printf("Does 35 exist ? : %d\n", list_contains(__head_sll1, 35));
    printf("Does 45 exist ? : %d\n", list_contains(__head_sll1, 45));
    printf("\n");
    reverse(&__head_sll1);
    traverse_sll(__head_sll1, "sll1");
    printf("\n");
    reverse(&__head_sll1);
    traverse_sll(__head_sll1, "sll1");

    /*
    if( insert_node_after_key(__head_sll1, "sll1", 40, 45) != 0 ) {
        exit(1);
    }
    else {
        printf("Node inserted ...\n");
    }
    */

    delete_node(&__head_sll1, "sll1", 20);
    delete_node(&__head_sll1, "sll1", 30);
    printf("Linked list sll1 has %lu nodes\n", ll_lenght(__head_sll1));
    traverse_sll(__head_sll1, "sll1");
    delete_node(&__head_sll1, "sll1", 10);
    printf("Linked list sll1 has %lu nodes\n", ll_lenght(__head_sll1));
    traverse_sll(__head_sll1, "sll1");
    printf("Does 10 exist ? : %d\n", list_contains(__head_sll1, 10));
    printf("Does 20 exist ? : %d\n", list_contains(__head_sll1, 20));
    printf("Does 30 exist ? : %d\n", list_contains(__head_sll1, 30));

    printf("\n\n");

    // Create empty single linked list 2 (no elements/nodes yet)
    node_s *__head_sll2 = NULL;

    if( append_node(&__head_sll2, "sll2", 100) == 0 ) {
        printf("Init node added ...\n");
    }
    else {
        exit(1);
    }

    if( append_node(&__head_sll2, "sll2", 200) == 0 ) {
        printf("Node added ...\n");
    }
    else {
        exit(1);
    }
    traverse_sll(__head_sll2, "sll2");

    return 0;
}

// Add a new node always at the end of the linked list
list_status append_node(node_s **sll_head, char *ll_name, int data) {

    // if __head_sll1 is NULL, list is empty so needs to be init it once!
    if(!(*sll_head)) {

        *sll_head = malloc(sizeof(node_s));
        if(!(*sll_head)) {
            printf("Memory allocation of init node failed!\n");
            return LIST_ERR_ALLOC;
        }
        (*sll_head)->data = data;
        (*sll_head)->next_node = NULL;

        DEBUG_PRINT("Init node of %s created at address %p with data %d\n", ll_name, *sll_head, (*sll_head)->data);

        return LIST_OK;
    }

    // Create and connect new node with the previous one
    node_s *n = malloc(sizeof(node_s));
    if(!n) {
        printf("Memory allocation of node failed!\n");
        return LIST_ERR_ALLOC;
    }
    n->next_node = NULL;
    n->data = data;

    node_s *cursor = *sll_head;
    for(cursor; cursor->next_node != NULL; 
                    cursor = cursor->next_node) {

        /* Do nothing */
    }
    cursor->next_node = n;
    
    DEBUG_PRINT("New node appended in %s at address %p with data %d\n", ll_name, n, n->data);

    return LIST_OK;
}

list_status insert_node_after_key(node_s *sll_head, char *ll_name, int key, int data) {

    node_s *k = NULL, *n = NULL;

    for(k = sll_head; k != NULL;
                       k = k->next_node) {

        if(k->data == key) {
            break;
        }
    }

    if(!k) {
        printf("Insertion failed: Key %d was not found!\n", key);
        return LIST_KEY_NOT_FOUND;
    }

    n = malloc(sizeof(node_s));
    if(!n) {
        printf("Memory allocation of node failed!\n");
        return LIST_ERR_ALLOC;
    }

    n->data = data;
    n->next_node = k->next_node;
    k->next_node = n;

    DEBUG_PRINT("New node inserted in %s after key %d at address %p with data %d\n", ll_name, key, n, n->data);

    return LIST_OK;
}

bool delete_node(node_s **sll_head, char *ll_name, int data) {
    
    for(node_s *p = NULL, *c = *sll_head; c != NULL; p = c, c = c->next_node) {
        if(c->data == data) {
            if(c == *sll_head) {
                (*sll_head) = c->next_node;
            }
            else {
                p->next_node = c->next_node;
            }
            printf("%s: Node at address %p with data %d just deleted\n", ll_name, c, data);
            free(c);
                        
            return true;
        }
    }
    return false;
}

list_status reverse(node_s **sll_head) {
    printf("Reversing ...\n");

    size_t ll_size = ll_lenght(*sll_head);

    // Allocate memory in heap and initialize to zero/NULL at once
    node_s **n_arr = calloc(ll_size, sizeof(*n_arr));
    if(!n_arr) {
        printf("Memory allocation failed!\n");
        return LIST_ERR_ALLOC;
    }

    size_t count = 0;
    for(node_s *cursor = *sll_head;
                cursor != NULL;
                cursor = cursor->next_node) {

        n_arr[count++] = cursor;
        // *(n_arr + count++) = cursor; // the sames
    }

    //__head now points to the last node of the reversed linked list
    *sll_head = n_arr[count-1];

    int i = 0;
    for(i = count - 1; i > 0; i--) {
        n_arr[i]->next_node = n_arr[i-1];
    }
    // The node that was previously pointed by the __head in now the last node in the reversed linked list
    n_arr[i]->next_node = NULL;

    return LIST_OK;
}

void traverse_sll(node_s *sll_head, char *ll_name) {

    size_t i = 0;
    for(node_s *cursor = sll_head; 
                cursor != NULL; 
                cursor = cursor->next_node) {
        
        printf("%s: Node[%ld] = %d at address %p\n", ll_name, i++, cursor->data, cursor);
    }
}

size_t ll_lenght(const node_s *sll_head) {
    size_t i = 0;
    for(const node_s *cursor = sll_head; 
                      cursor != NULL; 
                      cursor = cursor->next_node) {
        i++;
    }
    return i;
}

bool list_contains(const node_s *sll_head, int data) {
    for(const node_s *cursor = sll_head; cursor != NULL; cursor = cursor->next_node) {
        if(cursor->data == data) {
            return true;
        }
    }
    return false;
}