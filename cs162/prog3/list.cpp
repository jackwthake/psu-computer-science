/*
 * Jack Thake
 * CS162, Program 3, July 29th, 2020
 *
 * This file holds the implementation to my linear linked list class in the list
 * header file.
*/


#include "list.h"

#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;



/* constructor */
list::list() { /* we don't need to do anything here. */  }



/* loads in a file on creation */
list::list(const char *file_path) {
  ifstream data_file;
  data_file.open(file_path);

  if(!data_file)
    return;

  while(!data_file.eof()) {
    Pizza pizza; /* prepare one struct */
    
    /* read in all the member variables */
    data_file.get(pizza.name, field_length, '|');
    data_file.ignore(100, '|');
    data_file.get(pizza.description, field_length, '|');
    data_file.ignore(100, '|');
    data_file.get(pizza.additions, field_length, '|');
    data_file.ignore(100, '|');
    data_file.get(pizza.removals, field_length, '|');
    data_file.ignore(100, '|');
    
    data_file >> pizza.rating;
    data_file.ignore(100, '|');

    data_file >> pizza.price;
    data_file.ignore(100, '\n');

    if(strcmp(pizza.name, "") != 0) /* if an empty one is read, it is ignored. */
      this->add(pizza);
  }

  /* cleanup */
  data_file.close();
}



/* destructor */
list::~list() {
  node *current = this->head;

  while(current) {
    current = current->next; /* get the next item before the current one is deleted */
    delete current; 
  }

  this->head = nullptr;
  this->tail = nullptr;
}



/*
 * void list::add(const Pizza &pizza)
 *
 * brief: adds one pizza to the endd of the list
 * const Pizza &pizza: the pizza oto be added
*/
void list::add(const Pizza &pizza) {
  if(!this->head) { /* if the list is empty */
    this->head = new node; /* create the new node */
    this->head->data = pizza; /* set the data to the passed pizza */
 
    /* set head and tail pointers */   
    this->head->next = nullptr; /* set next to nullptr  */
    this->tail = head; /* only one item */
  } else {
    /* create the new node and shuffle forward the tail pointer */
    this->tail->next = new node; /* add a node to the end */
    this->tail = this->tail->next; /* move the tail to the next */

    /* set the node's members */
    this->tail->data = pizza;
    this->tail->next = nullptr; /* last element */ 
  }
}



/*
 * bool list::remove(char name[])
 *
 * brief: removes the list item with the same name passed into the function
 *
 * char name[]: the name of the pizza to be deleted
 * return: returns true if the item was deleted, false otherwise.
*/
bool list::remove(char name[]) {
  node *current = this->head;
  node *previous = this->head;

  while(current) {
    if(strcmp(current->data.name, name) == 0) {
      if(previous == this->head) {
        this->head = current->next;
        delete current;
      } else {
        if(current->next == nullptr) { /* if the one being deleted is the last element */
          previous->next = nullptr;
          this->tail = previous; /* move the tail backwards */
        } else
          previous->next = current->next; /* not the last element */

        delete current; /* delete the element */
      }

      return true; /* we've deleted the item, no need to keep searching */
    }

    previous = current;
    current = current->next;
  }

  return false; /* item wasn't found */
}



/*
 * void list::display_all()
 *
 * brief: lists all elements in the list.
*/
void list::display_all() {
  node *current = this->head;
  while(current) {
    std::cout << endl
              << "----------------------\n"
              << "Name: " << current->data.name << "\n"
              << "Description: " << current->data.description << "\n"
              << "Additions: " << current->data.additions << "\n"
              << "Removals: " << current->data.removals << "\n"
              << "Rating (Out of 5): " << current->data.rating << "\n" 
              << "Price: " << current->data.price << "\n" 
              << "----------------------\n" << endl;
    
    current = current->next;
  }
}



/*
 * const Pizza *list::exists(char name[])
 *
 * brief: searches the list for an item of the same name, returns it if found
 *        otherwise, returns and empty pizza struct.
 *
 * char name[]: the name of the item to be searched for
 * return: the matching pizza struct or an empty struct
*/
const Pizza *list::exists(char name[]) {
  node *current = this->head;
  while(current) {
    if(strcmp(current->data.name, name) == 0) {
      return &current->data;
    }

    current = current->next;
  }

  return nullptr;
}



/*
 * bool list::write_list_to_file(const char *file_path)
 *
 * brief: writes the current list to file, returns true if successful.
 *
 * const char *file_path: the file to be written to
 * return: true if successful, false otherwise.
*/
bool list::write_list_to_file(const char *file_path) {
  ofstream data_file;
  data_file.open(file_path);

  if(!data_file) /* if the file could not be opened, return */
    return false;

  node *current = this->head;
  while(current) {
    data_file << current->data.name << '|'
              << current->data.description << '|'
              << current->data.additions << '|'
              << current->data.removals << '|'
              << current->data.rating << '|'
              << current->data.price << endl;

    current = current->next;
  }

  data_file.close();
  return true;
}

