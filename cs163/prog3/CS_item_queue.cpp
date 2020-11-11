//
//  CS_item_queue.cpp
//  psu-computer-science
//
//  Created by Jack Thake on 11/11/2020.
//  This file holds the implementation of the CS_item_queue class
//

#include "CS_item_queue.h"
#include <cstddef>
#include <iostream>
using namespace std;

/* initialise queue */
CS_item_queue::CS_item_queue() {
  this->qptr = NULL;
}


/* deallocate */
CS_item_queue::~CS_item_queue() {
  /* uncircularise the list - makes it easier to deallocate */
  node *head = this->qptr->next;
  this->qptr->next = NULL;

  /* deallocate as if it were a LLL */
  while (head) {
    node *temp = head;
    head = head->next;

    delete temp;
  }
}


/* add to the rear of the queue */
CS_error CS_item_queue::enqueue(const CS_item_info &to_add) {
  if (!this->qptr) { /* empty queue */
    this->qptr = new node;
    this->qptr->data = to_add;
    this->qptr->next = this->qptr;

    return SUCCESS;
  }

  /* queue has atleast one item in it */
  node *temp = this->qptr->next;
  this->qptr->next = new node;
  this->qptr = this->qptr->next; /* we advance the rear of the queue */

  this->qptr->data = to_add;
  this->qptr->next = temp;

  return SUCCESS;
}


/* remove from front of the queue, giving back the previous front of list */
CS_error CS_item_queue::dequeue(CS_item_info &result) {
  if (!this->qptr) /* empty queue, nothing to remove */
    return FAILURE;

  node *temp = this->qptr->next->next; /* grab the new front of queue */
  result = this->qptr->next->data; /* give back the front of the queue */
  delete this->qptr->next; /* remove */
  this->qptr->next = temp; /* move the front */

  return SUCCESS;
}


/* gives back the front of the queue */
CS_error CS_item_queue::peak(CS_item_info &result) const {
  if (!this->qptr) /* empty queue */
    return FAILURE;

  /* give back result */
  result = this->qptr->next->data;
  return SUCCESS;
}


/* handler function for recursive print */
CS_error CS_item_queue::display() const {
  if (!this->qptr) /* empty queue */
    return FAILURE;

  if (this->qptr == this->qptr->next) { /* only one item in queue */
    this->qptr->data.print();
  } else { /* queue has atleast 2 items, display them all */
    this->display_recurs(this->qptr->next);
  }

  return SUCCESS;
}


/* recursive function to print each item in the queue */
void CS_item_queue::display_recurs(node *current) const {
  if (current == this->qptr) { /* last item in the queue */
    cout << "---------------------------------------" << endl;
    current->data.print();
    cout << "---------------------------------------" << endl;

    return;
  }
  
  /* print current data and move to next iteration */
  cout << "---------------------------------------" << endl;
  current->data.print();

  return display_recurs(current->next);
}

