// gcc sll_upd4_main.c sll_upd4.c -o sll_upd4
// ./sll_upd4

// OR

// gcc -DDEBUG=0 sll_upd4_main.c sll_upd4.c -o sll_upd4
// ./sll_upd4

#include "sll_upd4.h"
#include <stdio.h>
#include <stdlib.h>

#define CHECK_FATAL(x) do {                                                \
    sll_status st = (x);                                                   \
    if(st != SLL_SUCCESS) {                                                \
        fprintf(stderr, "Fatal: %s\n", sll_status_str(st));                \
        exit(EXIT_FAILURE);                                                \
    }                                                                      \
} while(0)

void print_node(node_s *n, size_t node_index, int data) {
    printf("Node[%ld] = %d at address %p\n", node_index, data, n);
}

int main(void) {

    sll_t *sll1 = sll_create();
    if(!sll1) {
        fprintf(stderr, "List memory allocation failed!\n");
        return EXIT_FAILURE;
    }

    sll_status status = 0;
    // status = sll_insert_node_after_key(sll1, 20, 25);
    // if(status == SLL_KEY_NOT_FOUND) {
    //     log_error(status);
    // }
    // else if(status != SLL_SUCCESS) {
    //     handle_error(status);
    // }
    // sll_traverse(sll1, print_node);

    // Fatal example
    CHECK_FATAL(sll_append_node(sll1, 10));
    CHECK_FATAL(sll_delete_node(sll1, 10));
    CHECK_FATAL(sll_append_node(sll1, 20));
    CHECK_FATAL(sll_append_node(sll1, 30));

    sll_traverse(sll1, print_node);

    // Non-fatal example
    status = sll_insert_node_after_key(sll1, 40, 40);
    if(status != SLL_SUCCESS) {
        fprintf(stderr, "%s\n", sll_status_str(status));
    }

    status = sll_insert_node_after_key(sll1, 20, 25);
    if(status != SLL_SUCCESS) {
        fprintf(stderr, "%s\n", sll_status_str(status));
    }

    status = sll_insert_node_after_key(sll1, 30, 35);
    if(status != SLL_SUCCESS) {
        fprintf(stderr, "%s\n", sll_status_str(status));
    }

    sll_traverse(sll1, print_node);

    CHECK_FATAL(sll_delete_node(sll1, 20));
    sll_traverse(sll1, print_node);

    /*
    // The following lines will return "Data provided not found!",
    // since you try to remove data that cannot be found in your
    // list since you removed them earlier!!!
    status = sll_delete_node(sll1, 10);
    if(status == SLL_INV_DATA) {
        log_error(status);
    }
    else if(status != SLL_SUCCESS) {
        handle_error(status);
    }
    sll_traverse(sll1, print_node);
    */

    /*
    status = sll_delete_node(sll1, 35);
    if(status == SLL_INV_DATA) {
        log_error(status);
    }
    else if(status != SLL_SUCCESS) {
        handle_error(status);
    }
    sll_traverse(sll1, print_node);
    */

    /*
    // The following lines will return "Container list is empty!", eventually,
    // since once you have deleted 25 and 30 and the list is empty
    // you try to remove data again !!!
    status = sll_delete_node(sll1, 25);
    if(status == SLL_INV_DATA) {
        log_error(status);
    }
    else if(status != SLL_SUCCESS) {
        handle_error(status);
    }
    sll_traverse(sll1, print_node);

    status = sll_delete_node(sll1, 30);
    if(status == SLL_INV_DATA) {
        log_error(status);
    }
    else if(status != SLL_SUCCESS) {
        handle_error(status);
    }
    sll_traverse(sll1, print_node);

    status = sll_delete_node(sll1, 10);
    if(status == SLL_INV_DATA) {
        log_error(status);
    }
    else if(status != SLL_SUCCESS) {
        handle_error(status);
    }
    sll_traverse(sll1, print_node);
    */

    //sll_length(NULL);

    DEBUG_PRINT("Before freeing: address linked list sll1 points to: %p\n", sll1);
    // The following format is called ternary expression
    (sll_destroy(&sll1) == SLL_NOT_FREED) ? printf("List not freed ... !\n") : printf("List freed ... !\n");
    DEBUG_PRINT("After freeing: address linked list sll1 points to: %p\n", sll1);
    
    return EXIT_SUCCESS;
}