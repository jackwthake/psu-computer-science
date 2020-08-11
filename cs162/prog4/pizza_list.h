#ifndef PIZZA_LIST_H
#define PIZZA_LIST_H

#include "pizza.h"

/* represents one node in the linked list */
struct node {
  pizza data;
  node *next;
};


/* represents one linked list */
class pizza_list {
  public:
    pizza_list(); /* constructor */
    ~pizza_list(); /* destructor */

    void add_pizza(); /* add a pizza, have the method create the pizza */
    void add_pizza(pizza &item); /* add a premade pizza to the list  */
    void remove_item(const char *name); /* remove specific item */
    void clear_list(); /* delete list */
    pizza *exists(const char *name) const; /* search for specific pizza */

    void displ_all() const; /* display all alphabetically */
    void displ_most_recent() const; /* display most recent addition */
    void displ_all_with_rating(unsigned rating) const; /* display all with a given rating */

  private:
    void bubble_sort(); /* sort the list */
    void write_to_file() const; /* write list to file */

    int length; /* length of list */
    node *head; /* start of list */
};

#endif
