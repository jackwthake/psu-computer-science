/*
 * Jack Thake
 * CS162, Program 3, July 29th, 2020
 *
 * This file holds the prototypes for the node struct, list class, as well as
 * their members. The list class represents one linear linked list while the
 * node struct represents one node inside the linked list.
*/

#ifndef LIST_H /* include guard */
#define LIST_H

#include "pizza.h"

struct node {
  Pizza data;
  node *next;
};

class list {
  public:
    list(); /* allocate */
    list(const char *file_path); /* load in a file on creation */
    ~list(); /* deallocate */

    void add(const Pizza &); /* add one item */
    bool remove(char[]); /* remove one item */
    void display_all(); /* list all items */

    const Pizza *exists(char[]); /* check if a pizza exists */

    bool write_list_to_file(const char *);
  private:
    node *head; /* start of list */
    node *tail; /* end of list */
};

#endif
