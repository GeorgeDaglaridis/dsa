#ifndef SLL_H
#define SLL_H

#include <stddef.h>

// gcc -DDEBUG=1 sll_upd3.c -o sll_upd3
#define DEBUG 1

#if DEBUG
    #define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...)
#endif

typedef enum {
    SLL_SUCCESS         =  0,
    SLL_ERR_ALLOC       = -1,
    SLL_ERR_INVALID_ARG = -2,
    SLL_EMPTY           = -3,
    SLL_INV_DATA        = -4,
    SLL_KEY_NOT_FOUND   = -5,
    SLL_NOT_FREED       = -6
} sll_status;

// Do not expose the elements/memebers of
// this structure to the user.
typedef struct node node_s;
typedef struct sll sll_t;

/***** Function prototypes/declarations *****/

// Create a single list list (sll)
sll_t *sll_create(void);
// Destroy/Free an sll
sll_status sll_destroy(sll_t **list);
// Append a node at the end of an sll
sll_status sll_append_node(sll_t *list, int data);
// Insert a node in an sll after a certain key
sll_status sll_insert_node_after_key(sll_t *list, int key, int data);
// Delete node from an sll
sll_status sll_delete_node(sll_t *list, int data);
// Traverse through all nodes of an sll
void sll_traverse(const sll_t *list, void (*visit)(node_s *, size_t, int));
// Size of an sll
size_t sll_size(const sll_t *list);
const char *sll_status_str(sll_status status);

#endif