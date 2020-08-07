#include "pizza_list.h"
#include <cstring>
#include <ctype.h>

#include <fstream>
using namespace std;

pizza_list::pizza_list() {
  this->head = nullptr;
  this->length = 0;
}

pizza_list::pizza_list(char *filepath) {
  ifstream data;
  data.open(filepath);

  this->head = nullptr;
  this->length = 0;
  this->fp = filepath;
  
  if(!data)
    return;

  while(!data.eof()) {
    pizza item;

    /* read in all the member variables */
    data.get(item.name, field_length, '|'); /* read in name member */
    data.ignore(100, '|');
    data.get(item.description, field_length, '|'); /* read in description member */
    data.ignore(100, '|');
    data.get(item.additions, field_length, '|'); /* read in additions member */
    data.ignore(100, '|');
    data.get(item.removals, field_length, '|'); /* read in removals member */
    data.ignore(100, '|');
    
    data >> item.rating; /* read in rating member */
    data.ignore(100, '|');

    data >> item.time_added; /* read in time_added member */
    data.ignore(100, '|');

    data >> item.price; /* read in price member */
    data.ignore(100, '\n');

    if(strcmp(item.name, "") != 0) /* if an empty one is read, it is ignored. */
      this->add_pizza(item);
  }
}

pizza_list::~pizza_list() {
  node *current, *next = this->head;
  
  this->write_to_file();

  while(next) {
    current = next;
    next = next->next;

    delete current;
  }
}

void pizza_list::add_pizza() {
  pizza addition;
  read_pizza_from_user(addition);

  this->add_pizza(addition);
}

void pizza_list::add_pizza(pizza &item) {
  if(this->head == nullptr) {
    this->head = new node;
    this->head->data = item;
    this->head->next = nullptr;
  } else {
    node *old_head = this->head;
    this->head = new node;
    this->head->data = item;
    this->head->next = old_head;
  }

  this->bubble_sort();

  ++length;
}

pizza *pizza_list::exists(const char *name) const {
  node *current = this->head;

  while(current) {
    if(strcmp(name, current->data.name) == 0) {
      return &current->data;
    }

    current = current->next;
  }

  return NULL;
}

void pizza_list::displ_all() const {
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

void pizza_list::displ_most_recent() const {
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

void pizza_list::displ_all_with_rating(unsigned rating) const {
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

void pizza_list::write_to_file() const {
  ofstream data_file;
  data_file.open(this->fp);

  if(!data_file) /* if the file could not be opened, return */
    return;

  /* get ready to go through the list */
  node *current = this->head;

  while(current) {
    /* write into the file each of the node's members, separated by '|'. */
    data_file << current->data.name << '|'
              << current->data.description << '|'
              << current->data.additions << '|'
              << current->data.removals << '|'
              << current->data.rating << '|'
              << current->data.price << '|'
              << current->data.time_added << endl;

    /* prepare for the next iteration */
    current = current->next;
  }

  /* cleanup after ourselves */
  data_file.close();  
}

