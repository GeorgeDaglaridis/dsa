#include "sll_upd4.h"
#include <stdio.h>
#include <stdlib.h>

// Represents each node of the linked list
struct node {
    int data;
    struct node *next_node;
};

// List container: Manages the list that manages nodes
struct sll {
    node_s *head;
    node_s *tail;
    size_t size;
};

// Helper function
// Prints nothing when DEBUG is 0
static void print_list_details(const sll_t *list, const char *msg) {
    if( (list->head == NULL) || (list->tail == NULL)) {
        DEBUG_PRINT("%s: list->head: %p, list->tail: %p, size: %ld\n", msg, list->head, list->tail, list->size);
    }
    else {
        DEBUG_PRINT("%s: list->head: %p, list->tail: %p, list->tail->next_node: %p, size: %ld\n", msg, list->head, list->tail, list->tail->next_node, list->size);
    }
}

sll_t *sll_create(void) {
    
    sll_t *list = calloc(1, sizeof(*list));
    if(!list) {
        return NULL;
    }
    printf("\nList creation: list->head: %p, list->tail: %p, size: %ld\n\n", list->head, list->tail, list->size);
    
    return list;
}

// Make sure you free all nodes first before you free
// the list container
sll_status sll_destroy(sll_t **list) {
    // Defensive check: Do not trust the arguments 
    // user provides you. Check for all cases.
    if( (list == NULL) || (*list == NULL) ) {
        return SLL_NOT_FREED;
    }

    // Free each node first ...
    node_s *cursor = (*list)->head;
    while(cursor != NULL) {

        node_s *temp_next_node = cursor->next_node;
        DEBUG_PRINT("Before freeing: address node cursor points to: %p\n", cursor);
        free(cursor);
        //cursor = NULL; redundant since it gets overwritten immediately below
        DEBUG_PRINT("After freeing: address node cursor points to: %p\n", cursor);
        cursor = temp_next_node;
    }
    // Restore list to valid empty state
    (*list)->head = NULL;
    (*list)->tail = NULL;
    (*list)->size = 0;
    // Then free the list container
    //DEBUG_PRINT("Before freeing: (*list)->head: %p, (*list)->tail: %p, (*list)->size: %ld\n", (*list)->head, (*list)->tail, (*list)->size);
    free(*list);
    //DEBUG_PRINT("After freeing: (*list)->head: %p, (*list)->tail: %p, (*list)->size: %ld\n", (*list)->head, (*list)->tail, (*list)->size);
    *list = NULL; // This way you modify the caller's pointer
    //DEBUG_PRINT("(*list)->head: %p, (*list)->tail: %p, (*list)->size: %ld\n", (*list)->head, (*list)->tail, (*list)->size);
    
    return SLL_SUCCESS;
}

// Basically append node at the end
sll_status sll_append_node(sll_t *list, int data) {

    // Defensive check: Do not trust the arguments 
    // user provides you. Check for all cases.
    if(list == NULL) { // List does not exist
        return SLL_ERR_INVALID_ARG;
    }

    node_s *n = calloc(1, sizeof(*n));
    if(!n) {
        return SLL_ERR_ALLOC;
    }
    n->next_node = NULL;
    n->data = data;

    char *msg = "Node";

    if(list->head == NULL) {
        list->head = n;
        list->tail = n; // Consequently, (*list)->tail->next_node = NULL;

        msg = "Init node";
        printf("%s created at address %p with data %d\n", msg, n, n->data);

    } else {
        // Connect old tail to the new node
        list->tail->next_node = n;
        // Update tail with the new node
        list->tail = n;

        printf("%s appended at address %p with data %d\n", msg, n, n->data);
    }
    // More clear but maybe not needed since n->next = NULL from above 
    // and now tail has been updating pointing to the last created and added node 
    list->tail->next_node = NULL; 
    list->size++;

    print_list_details(list, "Append node");

    return SLL_SUCCESS;
}

// There has to be at least one node in order to use this function
sll_status sll_insert_node_after_key(sll_t *list, int key, int data) {

    if(list == NULL) {
        return SLL_ERR_INVALID_ARG;
    }
    else if(list->head == NULL) {
        return SLL_EMPTY;
    }

    node_s *k = NULL, *n = NULL;

    for(k = list->head; k != NULL;
                      k = k->next_node) {

        if(k->data == key) {
            break;
        }
    }

    if(!k) {
        return SLL_KEY_NOT_FOUND;
    }

    n = calloc(1, sizeof(*n));
    if(!n) {
        return SLL_ERR_ALLOC;
    }
    //n->next_node = NULL;
    n->data = data;

    // General handling
    n->next_node = k->next_node;
    k->next_node = n;
    
    // Special handling
    if(k == list->tail) {
        list->tail = n;
        // Redunndant since you assigned n->next_node = NULL; before
        //list->tail->next_node = NULL;
    } 
    list->size++;

    printf("New node inserted after key %d at address %p with data %d\n", key, n, n->data);
    print_list_details(list, "Insert node");

    return SLL_SUCCESS;
}

// There has to be at least one node in order to use this function
sll_status sll_delete_node(sll_t *list, int data) {

    if(list == NULL) {
        return SLL_ERR_INVALID_ARG;
    }
    if(list->head == NULL) {
        return SLL_EMPTY;
    }

    node_s *prev, *curr;
    for(prev = NULL, curr = list->head;
                             curr != NULL;
                             prev = curr, curr = curr->next_node) {
        
        if(curr->data == data) {
            break;
        }
    }

    if(!curr) {
        return SLL_INV_DATA;
    }
    
    if(curr == list->head) {
        list->head = curr->next_node;
    }
    else {
        prev->next_node = curr->next_node;
    }
    
    if(curr == list->tail) {        
        list->tail = prev;

        // In case list has only the init node
        // and we want to delete it
        if(list->tail != NULL) {
            list->tail->next_node = NULL;
        }
    }
    printf("Node deletion: Node at address %p with data %d just deleted\n", curr, curr->data);
    free(curr);
    curr = NULL;
    list->size--;

    print_list_details(list, "Delete node");
    
    return SLL_SUCCESS;
}

size_t sll_length(const sll_t *list) {
    if(!list) {
        printf("NULL list!\n");
        return 0; // returning 0 is wrong but along with the msg before we shall understand
    }
    return list->size;
}

void sll_traverse(const sll_t *list, void (*visit)(node_s *, size_t, int)) {
    DEBUG_PRINT("Linked list sll1 has %ld nodes \n", sll_length(list));

    size_t i = 0;
    for(node_s *cursor = list->head; cursor != NULL; cursor = cursor->next_node) {
        visit(cursor, i++, cursor->data);
    }
}

const char *sll_status_str(sll_status status) {
    switch(status) {
        // Fail fast approach. Strict API
        case SLL_SUCCESS: return "SUCCESS";  
        case SLL_ERR_INVALID_ARG: return "NULL: Invalid argument provided!";        
        case SLL_ERR_ALLOC: return "Memory allocation of node failed!";       
        case SLL_EMPTY: return "Container list is empty!";
        case SLL_KEY_NOT_FOUND: return "Insertion failed: Key was not found!";
        case SLL_INV_DATA: return "Data provided not found!";
        default: return "Unknown error!";
    }

}
