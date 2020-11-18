/*
 * This file holds all implementations for the CS_item_queue class.
*/

#include "CS_item_queue.h"

#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

/* create queue */
CS_item_queue::CS_item_queue(const char *path) {
  this->ptr = NULL;
  char *buf = new char[51];

  ifstream fp;
  fp.open(path);
  if (!fp)
    return;

  do {
    fp.getline(buf, 51, '|'); /* get only the name attribute from the data file */
    fp.ignore(100, '\n');

    if (*buf) /* only add if its a valid string */
      this->enqueue(buf);
  } while (!fp.eof());

  fp.close();
  delete []buf;
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
      delete []this->ptr->next->data; /* free data */

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


/* print entire list, handler function for recursive call */
int CS_item_queue::print_all(void) const {
  if (!this->ptr)
    return 0;

  int count = 1;
  count += this->print_all_recurs(this->ptr->next, this->ptr, count);

  return count;
}


/* recursive print function */
int CS_item_queue::print_all_recurs(node *head, node *start, int count) const {
  if (!head)
    return 0;
  if (head == start) {
    cout << count << " | " << head->data << endl;
    return 1;
  }

  cout << count << " | " << head->data << endl;
  return 1 + this->print_all_recurs(head->next, start, count + 1);
}
