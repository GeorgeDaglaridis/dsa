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
    QUEUE_ERR_INVALID_ARG = -2,
} queue_status;

/**
 * @brief Opaque handle of a FIFO queue of int elements
 * 
 * A valid queue_s* is either NULL or a value returned by queue_create();
 * there is no other way to construct one. Caller must not access or assume any
 * layout for its members - the definition is private to queue.c and may change
 * without notice.
 * 
 * Ownership: the caller that receives a queue_s* from queue_create() owns it and
 * is responsible for destroying it via the matching destroy function. After destruction,
 * the pointer is dangling and must not be dereferenced or passed to any queue function.
 */
typedef struct queue queue_s; //Do not expose the elements/members of these structures to the user.

/************************* Function prototypes/declarations *************************/
/**
 * @brief Allocate and initialize a new, empty queue.
 * 
 * @return Pointer to the newly allocated queue_s with size 0 and
 *         no elements, or NULL if allocation fails.
 * 
 * @note The caller owns the returned queue and is responsible for
 *       eventually releassing it via the matching destroy function
 */
queue_s *queue_create();

/**
 * @brief Allocate a new node holding @p data and append it to the tail
 *        of the queue.
 * 
 * @param q    Address of the caller's queue pointer. Must not be NULL, and *q
 *             must already point to a queue previously returned by queue_create().
 * @param data Value to store in the new node.
 * 
 * @return QUEUE_ERR_INVALID_ARG if @p q or *q is NULL,
 *         QUEUE_ERR_ALLOC if new node's allocation failed,
 *         QUEUE_OK on success.
 */
int queue_enqueue(queue_s **q, int data);

/**
 * @brief Print the queue's internal details, then each node's data in 
 *        head-to-tail order.
 * 
 * @param q Queue to traverse. May be NULL.
 * 
 * @return QUEUE_ERR_INVALID_ARG if @p q is NULL, 
 *         QUEUE_OK on success (an empty queue is not an error: only the queue
 *         details are printed and not "Node" lines follow).
 * 
 * @note Read-only: does not modity @p q or any node it points to.
 */
int queue_traverse(const queue_s *q);


#endif // end of header file