#include "pizza_list.h"
#include "input.h"

#include <iostream>
#include <cstring>
using namespace std;

static void read_pizza_from_user(pizza &result) {
  /* read in pizza info */
  get_input_phrase("Enter the pizza's name: ", result.name, field_length);
  get_input_phrase("Enter a Description of the pizza: ", result.description, field_length);
  get_input_phrase("Enter any additions to the pizza: ", result.additions, field_length);
  get_input_phrase("Enter any removals from the pizza: ", result.removals, field_length);
  get_input("Enter a Rating from 0 to 5: ", result.rating);
  get_input_word("Enter the price: $", result.price);
}

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
    cout << endl
              << "---------- " << count << " ----------\n"
              << "Name: " << current->data.name << "\n"
              << "Description: " << current->data.description << "\n"
              << "Additions: " << current->data.additions << "\n"
              << "Removals: " << current->data.removals << "\n"
              << "Rating (Out of 5): " << current->data.rating << "\n" 
              << "Price: " << current->data.price << "\n" 
              << "----------------------\n" << endl;
    
    /* prepare for the next iteration */
    ++count;
    current = current->next;
  }
}

void pizza_list::displ_most_recent() {
  cout << endl
       << "------- Recent -------\n"
       << "Name: " << this->head->data.name << "\n"
       << "Description: " << this->head->data.description << "\n"
       << "Additions: " << this->head->data.additions << "\n"
       << "Removals: " << this->head->data.removals << "\n"
       << "Rating (Out of 5): " << this->head->data.rating << "\n" 
       << "Price: " << this->head->data.price << "\n" 
       << "----------------------\n" << endl;
}

void pizza_list::displ_all_with_rating(unsigned rating) {
  node *current = this->head;
  int count = 1;

  while(current) {
    if(current->data.rating == rating) {
      cout << endl
           << "---------- " << count << " ----------\n"
           << "Name: " << current->data.name << "\n"
           << "Description: " << current->data.description << "\n"
           << "Additions: " << current->data.additions << "\n"
           << "Removals: " << current->data.removals << "\n"
           << "Rating (Out of 5): " << current->data.rating << "\n" 
           << "Price: " << current->data.price << "\n" 
           << "----------------------\n" << endl;
      
      ++count;
    }

    current = current->next;
  }  
}

