#ifndef __H_QUEUE__
#define __H_QUEUE__

#include <stdbool.h>

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
    QUEUE_EMPTY = -3,
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
 * @param[in,out] q Address of the caller's queue pointer. Must not be NULL and 
 *                  on QUEUE_OK, *q is set to a newlly allocated queue.
 * 
 * @return QUEUE_ERR_INVALID_ARG if @p q is NULL,
 *         QUEUE_ERR_ALLOC if new queue's allocation failed,
 *         QUEUE_OK on success.
 * 
 * @note The caller owns the returned queue and is responsible for
 *       eventually releassing it via the matching destroy function
 */
queue_status queue_create(queue_s **q);

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
queue_status queue_enqueue(queue_s **q, int data);

/**
 * @brief Remove the queue's front element and hand its value back to the caller.
 * 
 * Detaches the node currently at @p q's head, copies its data out through @p out_data,
 * then frees the node's storage.
 *  
 * @param[in,out] q     Address of the caller's queue pointer. Must not be NULL and *q
 *                      must already point to a queue previously returned by queue_create().
 * @param[out] out_data Must not be NULL. On QUEUE_OK, receives the data held by the dequeued node.
 *                      Left unmodified if this function returns anything else.
 * 
 * @return QUEUE_ERR_INVALID_ARG if @p q, *q or @p out_data is NULL,
 *         QUEUE_EMPTY if the queue is empty,
 *         QUEUE_OK on success.
 */
queue_status queue_dequeue(queue_s **q, int *out_data);

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
queue_status queue_traverse(const queue_s *q);

/**
 * @brief Translate a queue_status value into a human-readable string.
 *
 * @param status Status value to describe, typically one returned by
 *               another queue_* function.
 *
 * @return A NUL-terminated string describing @p status, or "Unknown error!"
 *         if @p status does not match any known queue_status value.
 *
 * @note The returned pointer refers to a string literal: it must not be
 *       freed or written through, and it remains valid for the lifetime
 *       of the program.
 */
const char *queue_status_str(queue_status status);

#endif // end of header file