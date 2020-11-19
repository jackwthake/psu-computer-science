/*
 * Jack Thake, Program 3, Karla Fant
 * This file holds the declaration for the CS_item_table class, this class
 * implements a hash table, and loads it's contents from a file
*/

#ifndef CS_ITEM_TABLE_H
#define CS_ITEM_TABLE_H

#include "CS_item_info.h"
#include "CS_error.h"

class CS_item_table {
  public:
    CS_item_table(const char *, unsigned length = 7); /* load from file */
    ~CS_item_table(void); /* deallocate */

    CS_error add_item(const CS_item_info &); /* add item to hash table */
    CS_error remove_item(const char *); /* remove a specific item */
    CS_error remove_all(void); /* clear the list */
    CS_error retrieve(const char *, CS_item_info &); /* retrieve a specific item */
    CS_error print_all(void) const; /* print list, wrapper for recursive function */
  private:
    struct node {
      CS_item_info data;
      node *next;
    };

    node **table;
    unsigned length;
  private:
    unsigned hash_function(const char *) const; /* hash function used */
    void print_chain_recurs(node *, bool) const; /* recursive funciton to print chain contents */
};

#endif
