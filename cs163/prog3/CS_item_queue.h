//
//  CS_item_queue.h
//  psu-computer-science
//
//  Created by Jack Thake on 11/11/2020.
//  This file holds the declarations for the CS_item_queue class
//

#ifndef CS_ITEM_QUEUE
#define CS_ITEM_QUEUE

#include "CS_item_info.h"
#include "CS_error.h"

class CS_item_queue {
  public:
    CS_item_queue(); /* construct qeue */
    ~CS_item_queue(); /* deallocate */

    CS_error enqueue(const CS_item_info &); /* add to queue */
    CS_error dequeue(CS_item_info &); /* remove from queue storing what was removed */
    CS_error peak(CS_item_info &) const; /* store front of queue */
    CS_error display() const; /* print to user */

    /* check if queue is empty */
    inline bool is_empty() const { return !qptr; }
  private:
    struct node {
      CS_item_info data;
      node *next;
    };

    void display_recurs(node *current) const; /* recursively print */
    node *qptr; /* rear of queue */
};

#endif

