#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

#if DEBUG
    #define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...)
#endif

typedef struct node {
    int data;
    struct node *next_node;

} node_s;

// Add a new node always at the end of the linked list
int append_node(node_s **sll_head, char *ll_name, int data) {

    // if __head_sll1 is NULL, list is empty so needs to be init it once!
    if(!(*sll_head)) {

        *sll_head = malloc(sizeof(node_s));
        if(!(*sll_head)) {
            printf("Memory allocation of init node failed!\n");
            return -1;
        }
        (*sll_head)->data = data;
        (*sll_head)->next_node = NULL;

        DEBUG_PRINT("Init node of %s created at address %p with data %d\n", ll_name, *sll_head, (*sll_head)->data);

        return 0;
    }

    // Create and connect new node with the previous one
    node_s *n = malloc(sizeof(node_s));
    if(!n) {
        printf("Memory allocation of node failed!\n");
        return -1;
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

    return 0;
}

int insert_node_after_key(node_s *sll_head, char *ll_name, int key, int data) {

    node_s *k = NULL, *n = NULL;

    for(k = sll_head; k != NULL;
                       k = k->next_node) {

        if(k->data == key) {
            break;
        }
    }

    if(!k) {
        printf("Insertion failed: Key %d was not found!\n", key);
        return -2;
    }

    n = malloc(sizeof(node_s));
    if(!n) {
        printf("Memory allocation of node failed!\n");
        return -1;
    }

    n->data = data;
    n->next_node = k->next_node;
    k->next_node = n;

    DEBUG_PRINT("New node inserted in %s after key %d at address %p with data %d\n", ll_name, key, n, n->data);

    return 0;
}

void traverse_sll(node_s *sll_head, char *ll_name) {

    size_t i = 0;
    for(node_s *cursor = sll_head; 
                cursor != NULL; 
                cursor = cursor->next_node) {
        
        printf("%s: Node[%ld] = %d at address %p\n", ll_name, i++, cursor->data, cursor);
    }
}

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
    traverse_sll(__head_sll1, "sll1");

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
    traverse_sll(__head_sll1, "sll1");

    if( insert_node_after_key(__head_sll1, "sll1", 40, 45) != 0 ) {
        exit(1);
    }
    else {
        printf("Node inserted ...\n");
    }

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