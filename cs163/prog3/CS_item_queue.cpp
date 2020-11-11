#include "CS_item_queue.h"
#include <cstddef>
#include <iostream>
using namespace std;

CS_item_queue::CS_item_queue() {
  this->qptr = NULL;
}


CS_item_queue::~CS_item_queue() {
  node *head = this->qptr->next;
  this->qptr->next = NULL;

  while (head) {
    node *temp = head;
    head = head->next;

    delete temp;
  }
}


CS_error CS_item_queue::enqueue(const CS_item_info &to_add) {
  if (!this->qptr) {
    this->qptr = new node;
    this->qptr->data = to_add;
    this->qptr->next = this->qptr;

    return SUCCESS;
  }

  node *temp = this->qptr->next;
  this->qptr->next = new node;
  this->qptr = this->qptr->next;

  this->qptr->data = to_add;
  this->qptr->next = temp;

  return SUCCESS;
}


CS_error CS_item_queue::dequeue(CS_item_info &result) {
  if (!this->qptr)
    return FAILURE;

  node *temp = this->qptr->next->next;
  result = this->qptr->next->data;
  delete this->qptr->next;
  this->qptr->next = temp;

  return SUCCESS;
}


CS_error CS_item_queue::peak(CS_item_info &result) const {
  if (!this->qptr)
    return FAILURE;

  result = this->qptr->next->data;
  return SUCCESS;
}


CS_error CS_item_queue::display() const {
  if (!this->qptr)
    return FAILURE;
  
  if (this->qptr == this->qptr->next) {
    this->qptr->data.print();
  } else {
    this->display_recurs(this->qptr->next);
  }

  return SUCCESS;
}


void CS_item_queue::display_recurs(node *current) const {
  if (current == this->qptr) {
    cout << "---------------------------------------" << endl;
    current->data.print();
    cout << "---------------------------------------" << endl;

    return;
  }
  
  cout << "---------------------------------------" << endl;
  current->data.print();

  return display_recurs(current->next);
}

