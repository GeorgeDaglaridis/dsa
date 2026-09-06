#ifndef __H_QUEUE__
#define __H_QUEUE__

#define DEBUG 1

#if DEBUG
    # define DEBUG_PRINT(...) printf(__VA_ARGS__);
#else
    # define DEBUG_PRINT(...)
#endif

typedef enum {
    QUEUE_OK = 0,
    QUEUE_ERR_ALLOC = -1,
    QUEUE_ERR_INVALID_ARG = -2

} queue_status;

// Do not expose the elements/members of
// these structures to the user.
typedef struct queue queue_s;
typedef struct node node_s;

/***** Function prototypes/declarations *****/

queue_s *queue_create();
int enqueue(queue_s **q, int data);


#endif // end of header file