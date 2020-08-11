#include "pizza_list.h"
#include <cstring>
#include <ctype.h>

#include <fstream>
#include <iostream>
using namespace std;

/* creates a linear linked list, reads in from a file */
pizza_list::pizza_list() {
  /* initialise file */
  ifstream data;
  data.open("pizza.txt");

  /* init member vars */
  this->head = nullptr;
  this->length = 0;

  /* if the file doesn't exist */
  if(!data)
    return;

  /* while theres more to read */
  while(!data.eof()) {
    pizza item; /* item to be added */

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

  /* cleanup */
  data.close();
}


/* destructor */
pizza_list::~pizza_list() {
  this->write_to_file(); /* write list to file */
  this->clear_list(); /* destroy list and empty memory */
}


/* add one pizza to the list  */
void pizza_list::add_pizza() {
  pizza addition; /* pizza to be added */
  read_pizza_from_user(addition); /* read in all pizza info from user */

  /* add to the list */
  this->add_pizza(addition);
}


/* add a specific pizza to the list */
void pizza_list::add_pizza(pizza &item) {
  /* logic for insertion */
  if(this->head == nullptr) { /* if the list is empty */
    this->head = new node;
    this->head->data = item;
    this->head->next = nullptr;
  } else { /* not empty list */
    node *old_head = this->head;
    this->head = new node;
    this->head->data = item;
    this->head->next = old_head;
  }

  /* sort list alphabetically */
  this->bubble_sort();

  /* increment list length */
  ++this->length;
}


/* remove pizza with a specific name */
void pizza_list::remove_item(const char *name) {
  /* get ready for traversal */
  node *current = this->head, *previous = this->head;

  /* loop until the end of the list */
  while(current) {
    if(strcmp(name, current->data.name) == 0) {
      previous->next = current->next; /* unlink the matched node */
      
      /* deallocate the now unlinked node */
      delete current;

      /* exit as we've already deleted */
      return;
    }

    /* prep for next iteration */
    previous = current;
    current = current->next;
  }
}


/* remove all from list */
void pizza_list::clear_list() {
  /* get ready for traversal*/
  node *current = this->head, *previous = this->head;

  while(current) {
    if(current == previous) { /* if we're pointing at head */
      this->head = current->next; /* unlink first elemont */
      delete current; /* deallocate */
    } else if(!current->next) { /* last element */
      previous->next = nullptr; /* unlink item */
      delete current; /* deallocate */
    } else { /* middle of list */
      previous->next = current->next; /* unlink node */
      delete current; /* deallocate */
    }

    /* prep for next iteration */
    previous = current;
    current = current->next;
  }

  /* clear head pointer as it's memory has all been deallocated */
  this->head = nullptr;
}


/* search for a given pizza */
pizza *pizza_list::exists(const char *name) const {
  /* get ready for traversal */
  node *current = this->head;

  while(current) {
    if(strcmp(name, current->data.name) == 0) {
      return &current->data; /* return the match */
    }

    /* prep for next iteration */
    current = current->next;
  }

  /* if we reach this then we didn't find any matching pizza */
  return NULL;
}


/* display all in the lists alphabetical order */
void pizza_list::displ_all() const {
  /* get ready for traversal */
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


/* display the most recent addition to the list */
void pizza_list::displ_most_recent() const {
  /* get ready for traversale */
  node *current = this->head, *most_recent = nullptr;

  while(current) {
    if(most_recent) { /* if we've already found a recent node in the past iterations */
      if(current->data.time_added > most_recent->data.time_added) /* compare times  */
        most_recent = current;
    } else /* set most recent to the current as we don't have another one */
      most_recent = current;

    /* prep for next iteration */
    current = current->next;
  }

  /* print the result */
  print_pizza(most_recent->data);
}


/* display all with a certain rating */
void pizza_list::displ_all_with_rating(unsigned rating) const {
  /* prep for next iteration */
  node *current = this->head;
  int count = 1;

  while(current) {
    if(current->data.rating == rating) {
      print_pizza(current->data); /* if the ratings match, print */
      
      ++count;
    }

    /* prep for next iteration */
    current = current->next;
  }  
}


/* sort the list alphabetically  */
void pizza_list::bubble_sort() {
  int changes;
  node *current, *previous;

  do {
    changes = 0;
    current = previous = this->head;

    while(current) {
      if(current != previous) { /* if the current node isn't head */
        /* if the ascii value of the first char is greator, swap values */
        if(strcmp(current->data.name, previous->data.name) < 0) {
          pizza temp = previous->data;

          previous->data = current->data;
          current->data = temp;

          /* increment amound of changes on the current iteration */
          ++changes;
        }
      }

      /* prep for next iteration */
      previous = current;
      current = current->next;
    }
  } while(changes > 0); /* we loop until we haven't needed to change anything in the list */
}


/* write the list to file */
void pizza_list::write_to_file() const {
  ofstream data_file;
  data_file.open("pizza.txt");

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
              << current->data.time_added << '|'
              << current->data.price << endl;

    /* prepare for the next iteration */
    current = current->next;
  }

  /* cleanup after ourselves */
  data_file.close();  
}

