#include "CS_item_queue.h"

#include <cstring>
#include <cstdlib>

/* create queue */
CS_item_queue::CS_item_queue(void) {
  this->ptr = NULL;
}


/* destroy queue */
CS_item_queue::~CS_item_queue(void) {
  if (!this->ptr) /* empty list */
    return;

  node *head = this->ptr->next;

  /* deallocate as if it were a LLL */
  while (head != this->ptr) {
    node *temp = head; /* grab the current node */
    head = head->next; /* advance loop */

    delete []temp->data;
    delete temp; /* delete node */
  }

  /* clear final node */
  delete this->ptr;
  this->ptr = NULL;
} 


/* add to queue */
CS_error CS_item_queue::enqueue(const char *to_add) {
  if (!this->ptr) { /* empty queue */
    this->ptr = new node;
    this->ptr->data = new char[strlen(to_add) + 1];
    strcpy(this->ptr->data, to_add);

    this->ptr->next = this->ptr;

    return SUCCESS;
  }

  /* queue has atleast one item in it */
  node *temp = this->ptr->next;
  this->ptr->next = new node;
  this->ptr = this->ptr->next; /* we advance the rear of the queue */

  this->ptr->data = new char[strlen(to_add) + 1];
  strcpy(this->ptr->data, to_add);
  this->ptr->next = temp;

  return SUCCESS;
}


/* remove from queue */
CS_error CS_item_queue::dequeue(void) {
  if (!this->ptr) /* empty queue, nothing to remove */
    return FAILURE;
  else if (this->ptr->next == this->ptr) {
    delete []this->ptr->data;
    delete this->ptr;
    this->ptr = NULL;

    return SUCCESS;
  } else {
    node *temp = this->ptr->next->next; /* grab the new front of queue */
  
    if (this->ptr->next->data)
      free(this->ptr->next->data); /* free data */
  
    delete this->ptr->next; /* remove */
    this->ptr->next = temp; /* move the front */

    return SUCCESS;
  }
}


/* get front of queue */
char *CS_item_queue::peak(void) const {
  char *result = NULL;
  if (!this->ptr)
    return NULL;

  result = new char[strlen(this->ptr->next->data) + 1];
  strcpy(result, this->ptr->next->data);

  return result;
}


//int CS_item_queue::print_all(void) const; /* print entire list, handler function for recursive call */
