#ifndef __H_QUEUE__
#define __H_QUEUE__

// Do not expose the elements/members of
// these structures to the user.
typedef struct queue queue_s;
typedef struct node node_s;

/***** Function prototypes/declarations *****/

queue_s *queue_create();


#endif // end of header file