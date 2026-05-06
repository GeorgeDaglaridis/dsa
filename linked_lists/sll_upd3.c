#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// gcc -DDEBUG=1 sll_upd3.c -o sll_upd3
#define DEBUG 1

#if DEBUG
    #define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...)
#endif

typedef enum {
    SUCCESS = 0,
    LIST_NOK = -1,
    LIST_EMPTY = -2,
    LIST_ALRD_INIT = -3,
    LIST_ERR_ALLOC = -4,
    LIST_INV_DATA = -5,
    LIST_KEY_NOT_FOUND = -6,
    LIST_NOT_FREED = -7,
    LIST_ERR_INVALID_ARG = -8
} list_status;

// Represents each node of the linked list
typedef struct node {
    int data;
    struct node *next_node;
} node_s;

// List container: Manages the list that manages nodes
typedef struct list {
    node_s *head;
    node_s *tail;
    size_t size;
} list_s;

// Function prototypes/declarations
list_s *list_create(void);
list_status list_destroy(list_s **ll);
list_status append_node(list_s *ll, int data);
list_status insert_node_after_key(list_s *ll, int key, int data);
list_status delete_node(list_s *ll, int data);
size_t sll_length(const list_s *ll);
void traverse_sll(const list_s *ll);
void print_list_details(const list_s *ll, const char *msg);
void handle_error(list_status status);
void log_error(list_status status);

int main(void) {

    list_s *sll1 = list_create();
    if(!sll1) {
        printf("Llist memory allocation failed!\n");
        return LIST_ERR_ALLOC;
    }

    list_status status = 0;

    // status = insert_node_after_key(sll1, 20, 25);
    // if(status == LIST_KEY_NOT_FOUND) {
    //     log_error(status);
    // }
    // else if(status != SUCCESS) {
    //     handle_error(status);
    // }
    // traverse_sll(sll1);

    status = append_node(sll1, 10);
    if(status != SUCCESS) {
        handle_error(status);
    }

    status = delete_node(sll1, 10);
    if(status == LIST_INV_DATA) {
        log_error(status);
    }
    else if(status != SUCCESS) {
        handle_error(status);
    }
    traverse_sll(sll1);
    
    status = append_node(sll1, 20);
    if(status != SUCCESS) {
        handle_error(status);
    }

    status = append_node(sll1, 30);
    if(status != SUCCESS) {
        handle_error(status);
    }
    traverse_sll(sll1);    

    status = insert_node_after_key(sll1, 20, 25);
    if(status == LIST_KEY_NOT_FOUND) {
        log_error(status);
    }
    else if(status != SUCCESS) {
        handle_error(status);
    }
    traverse_sll(sll1);

    status = insert_node_after_key(sll1, 30, 35);
    if(status == LIST_KEY_NOT_FOUND) {
        log_error(status);
    }
    else if(status != SUCCESS) {
        handle_error(status);
    }
    traverse_sll(sll1);

    status = delete_node(sll1, 20);
    if(status == LIST_INV_DATA) {
        log_error(status);
    }
    else if(status != SUCCESS) {
        handle_error(status);
    }
    traverse_sll(sll1);

    /*
    // The following lines will return "Data provided not found!",
    // since you try to remove data that cannot be found in your
    // list since you removed them earlier!!!
    status = delete_node(sll1, 10);
    if(status == LIST_INV_DATA) {
        log_error(status);
    }
    else if(status != SUCCESS) {
        handle_error(status);
    }
    traverse_sll(sll1);
    */

    status = delete_node(sll1, 35);
    if(status == LIST_INV_DATA) {
        log_error(status);
    }
    else if(status != SUCCESS) {
        handle_error(status);
    }
    traverse_sll(sll1);

    /*
    // The following lines will return "Container list is empty!", eventually,
    // since once you have deleted 25 and 30 and the list is empty
    // you try to remove data again !!!
    status = delete_node(sll1, 25);
    if(status == LIST_INV_DATA) {
        log_error(status);
    }
    else if(status != SUCCESS) {
        handle_error(status);
    }
    traverse_sll(sll1);

    status = delete_node(sll1, 30);
    if(status == LIST_INV_DATA) {
        log_error(status);
    }
    else if(status != SUCCESS) {
        handle_error(status);
    }
    traverse_sll(sll1);

    status = delete_node(sll1, 10);
    if(status == LIST_INV_DATA) {
        log_error(status);
    }
    else if(status != SUCCESS) {
        handle_error(status);
    }
    traverse_sll(sll1);
    */

    //sll_length(NULL);

    DEBUG_PRINT("Before freeing: address linked list sll1 points to: %p\n", sll1);
    // The following format is called ternary expression
    (list_destroy(&sll1) == LIST_NOT_FREED) ? printf("List not freed ... !\n") : printf("List freed ... !\n");
    DEBUG_PRINT("After freeing: address linked list sll1 points to: %p\n", sll1);
    
    return 0;
}

list_s *list_create(void) {
    
    list_s *ll = calloc(1, sizeof(*ll));
    if(!ll) {
        return NULL;
    }
    // Hence:
    // ll->head = NULL;
    // ll->tail = NULL;
    // ll->tail->next_node = NULL; // if printed results in an error since list has no nodes
    // ll->size = 0;
    printf("\nList creation: ll->head: %p, ll->tail: %p, size: %ld\n\n", ll->head, ll->tail, ll->size);
    // DEBUG_PRINT("ll points to %p\n", ll);
    // DEBUG_PRINT("address of ll->head %p\n", &(ll->head));
    // DEBUG_PRINT("address of ll->tail %p\n", &(ll->tail));
    // DEBUG_PRINT("address of ll->size %p\n", &(ll->size));

    return ll;
}

// Make sure you free all nodes first before you free
// the list container
list_status list_destroy(list_s **ll) {
    // Defensive check: Do not trust the arguments 
    // user provides you. Check for all cases.
    if( (ll == NULL) || (*ll == NULL) ) {
        return LIST_NOT_FREED;
    }
    else {
        // Free each node first ...
        node_s *cursor = (*ll)->head;
        while(cursor != NULL) {

            node_s *temp_next_node = cursor->next_node;
            DEBUG_PRINT("Before freeing: address node cursor points to: %p\n", cursor);
            free(cursor);
            //cursor = NULL; redundant since it gets overwritten immediately below
            DEBUG_PRINT("After freeing: address node cursor points to: %p\n", cursor);
            cursor = temp_next_node;
        }
        // Restore list to valid empty state
        (*ll)->head = NULL;
        (*ll)->tail = NULL;
        (*ll)->size = 0;
        // Then free the list container
        //DEBUG_PRINT("Before freeing: (*ll)->head: %p, (*ll)->tail: %p, (*ll)->size: %ld\n", (*ll)->head, (*ll)->tail, (*ll)->size);
        free(*ll);
        //DEBUG_PRINT("After freeing: (*ll)->head: %p, (*ll)->tail: %p, (*ll)->size: %ld\n", (*ll)->head, (*ll)->tail, (*ll)->size);
        *ll = NULL; // This way you modify the caller's pointer
        //DEBUG_PRINT("(*ll)->head: %p, (*ll)->tail: %p, (*ll)->size: %ld\n", (*ll)->head, (*ll)->tail, (*ll)->size);
    }
    return SUCCESS;
}

// Basically append node at the end
list_status append_node(list_s *ll, int data) {

    // Defensive check: Do not trust the arguments 
    // user provides you. Check for all cases.
    if(ll == NULL) { // List does not exist
        return LIST_ERR_INVALID_ARG;
    }

    node_s *n = calloc(1, sizeof(*n));
    if(!n) {
        return LIST_ERR_ALLOC;
    }
    n->next_node = NULL;
    n->data = data;

    char *msg = "Node";

    if(ll->head == NULL) {
        ll->head = n;
        ll->tail = n; // Consequently, (*ll)->tail->next_node = NULL;

        msg = "Init node";
        printf("%s created at address %p with data %d\n", msg, n, n->data);

    } else {
        // Connect old tail to the new node
        ll->tail->next_node = n;
        // Update tail with the new node
        ll->tail = n;

        printf("%s appended at address %p with data %d\n", msg, n, n->data);
    }
    // More clear but maybe not needed since n->next = NULL from above 
    // and now tail has been updating pointing to the last created and added node 
    ll->tail->next_node = NULL; 
    ll->size++;

    print_list_details(ll, "Append node");

    return SUCCESS;
}

// There has to be at least one node in order to use this function
list_status insert_node_after_key(list_s *ll, int key, int data) {

    if(ll == NULL) {
        return LIST_ERR_INVALID_ARG;
    }
    else if(ll->head == NULL) {
        return LIST_EMPTY;
    }

    node_s *k = NULL, *n = NULL;

    for(k = ll->head; k != NULL;
                      k = k->next_node) {

        if(k->data == key) {
            break;
        }
    }

    if(!k) {
        return LIST_KEY_NOT_FOUND;
    }

    n = calloc(1, sizeof(*n));
    if(!n) {
        return LIST_ERR_ALLOC;
    }
    //n->next_node = NULL;
    n->data = data;

    // General handling
    n->next_node = k->next_node;
    k->next_node = n;
    
    // Special handling
    if(k == ll->tail) {
        ll->tail = n;
        // Redunndant since you assigned n->next_node = NULL; before
        //ll->tail->next_node = NULL;
    } 
    ll->size++;

    printf("New node inserted after key %d at address %p with data %d\n", key, n, n->data);
    print_list_details(ll, "Insert node");

    return SUCCESS;
}

// There has to be at least one node in order to use this function
list_status delete_node(list_s *ll, int data) {

    if(ll == NULL) {
        return LIST_ERR_INVALID_ARG;
    }
    if(ll->head == NULL) {
        return LIST_EMPTY;
    }

    node_s *prev, *curr;
    for(prev = NULL, curr = ll->head;
                             curr != NULL;
                             prev = curr, curr = curr->next_node) {
        
        if(curr->data == data) {
            break;
        }
    }

    if(!curr) {
        return LIST_INV_DATA;
    }
    
    if(curr == ll->head) {
        ll->head = curr->next_node;
    }
    else {
        prev->next_node = curr->next_node;
    }
    
    if(curr == ll->tail) {        
        ll->tail = prev;

        // In case list has only the init node
        // and we want to delete it
        if(ll->tail != NULL) {
            ll->tail->next_node = NULL;
        }
    }
    printf("Node deletion: Node at address %p with data %d just deleted\n", curr, curr->data);
    free(curr);
    curr = NULL;
    ll->size--;

    print_list_details(ll, "Delete node");
    
    return SUCCESS;
}

size_t sll_length(const list_s *ll) {
    if(!ll) {
        printf("NULL list!\n");
        return 0; // returning 0 is wrong but along with the msg before we shall understand
    }
    return ll->size;
}

void traverse_sll(const list_s *ll) {
    printf("Linked list sll1 has %ld nodes \n", sll_length(ll));

    size_t i = 0;
    for(node_s *cursor = ll->head; cursor != NULL; cursor = cursor->next_node) {
        printf("Node[%ld] = %d at address %p\n", i++, cursor->data, cursor);
    }
}

void print_list_details(const list_s *ll, const char *msg) {
    if( (ll->head == NULL) || (ll->tail == NULL)) {
        DEBUG_PRINT("%s: ll->head: %p, ll->tail: %p, size: %ld\n", msg, ll->head, ll->tail, ll->size);
    }
    else {
        DEBUG_PRINT("%s: ll->head: %p, ll->tail: %p, ll->tail->next_node: %p, size: %ld\n", msg, ll->head, ll->tail, ll->tail->next_node, ll->size);
    }
}

void handle_error(list_status status) {
    switch(status) {
        // Fail fast approach. Strict API
        case LIST_ERR_INVALID_ARG:
            fprintf(stderr, "NULL: Invalid argument provided!\n");
            break;
        
        case LIST_ERR_ALLOC:
            fprintf(stderr, "Memory allocation of node failed!\n");
            break;
        
        case LIST_EMPTY:
            fprintf(stderr, "Container list is empty!\n");
            break;
    }

    exit(EXIT_FAILURE);
}

void log_error(list_status status) {
    switch(status) {
        case LIST_KEY_NOT_FOUND:
            printf("Insertion failed: Key was not found!\n");
            break;
        
        case LIST_INV_DATA:
            printf("Data provided not found!\n");
            break;
    }
}