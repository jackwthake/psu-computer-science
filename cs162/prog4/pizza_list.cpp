#include "pizza_list.h"
#include <cstring>
#include <ctype.h>

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

  this->bubble_sort();

  ++length;
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
  node *current = this->head, *most_recent = nullptr;

  while(current) {
    if(most_recent) {
      if(current->data.time_added > most_recent->data.time_added)
        most_recent = current;
    } else
      most_recent = current;

    current = current->next;
  }

  print_pizza(most_recent->data);
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

void pizza_list::bubble_sort() {
  int changes;
  node *current, *previous;

  do {
    changes = 0;
    current = previous = this->head;

    while(current) {
      if(current != previous) {
        if(tolower(previous->data.name[0]) > tolower(current->data.name[0])) {
          pizza temp = previous->data;

          previous->data = current->data;
          current->data = temp;

          ++changes;
        }
      }

      previous = current;
      current = current->next;
    }
  } while(changes > 0);
}

