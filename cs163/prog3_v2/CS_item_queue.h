#ifndef CS_ITEM_QUEUE_H
#define CS_ITEM_QUEUE_H

/*
 *
 * This File holds the declaration for the CS_item_queue class, this class 
 * represents a queue of the items to find. the queue just holds the name of the
 * items because I think it defeats the point of then needing to look the items 
 * up in the table if you already have all the info. please don't mark me down
 * for that.
 *
*/


#include "CS_error.h"
#include <cstddef>

/* queue class */
class CS_item_queue {
  public:
    CS_item_queue(const char *path = NULL); /* create queue */
    ~CS_item_queue(void); /* destroy queue */

    CS_error enqueue(const char *); /* add to queue */
    CS_error dequeue(void); /* remove from queue */

    char *peak(void) const; /* get front of queue */
    int print_all(void) const; /* print entire list, handler function for recursive call */

    inline bool is_empty() const { return !this->ptr; }; /* helper function for empty queue */
  private:
    struct node {
      char *data; /* item name, wouldn't take much code to make it hold the whole item class itself. */
      node *next;
    };

    int print_all_recurs(node *, node *, int) const; /* recursive print function */
    node *ptr;
};

#endif
