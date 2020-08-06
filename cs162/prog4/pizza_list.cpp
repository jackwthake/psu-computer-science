#include "pizza_list.h"
#include <cstring>

pizza_list::pizza_list() {
  this->head = nullptr;
  this->length = 0;
}

pizza_list::~pizza_list() {
  node *current, *next = this->head;
  
  while(next) {
    current = next;
    next = next->next;

    delete current;
  }
}

void pizza_list::add_pizza() {
  pizza addition;
  read_pizza_from_user(addition);

  if(this->head == nullptr) {
    this->head = new node;
    this->head->data = addition;
    this->head->next = nullptr;
  } else {
    node *old_head = this->head;
    this->head = new node;
    this->head->data = addition;
    this->head->next = old_head;
  }
}

pizza *pizza_list::exists(const char *name) {
  node *current = this->head;

  while(current) {
    if(strcmp(name, current->data.name) == 0) {
      return &current->data;
    }

    current = current->next;
  }

  return NULL;
}

void pizza_list::displ_all() {
  node *current = this->head;
  int count = 1;
  
  while(current) {
    /* print out the current node's members */
    print_pizza(current->data);

    /* prepare for the next iteration */
    ++count;
    current = current->next;
  }
}

void pizza_list::displ_most_recent() {
  print_pizza(this->head->data);
}

void pizza_list::displ_all_with_rating(unsigned rating) {
  node *current = this->head;
  int count = 1;

  while(current) {
    if(current->data.rating == rating) {
      print_pizza(current->data);
      
      ++count;
    }

    current = current->next;
  }  
}

