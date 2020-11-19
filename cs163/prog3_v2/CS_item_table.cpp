/*
 * Jack Thake, Program 3, Karla Fant
 * This file holds all implementations for the CS_item_table class
*/

#include "CS_item_table.h"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

/* Construct a table from a file */
CS_item_table::CS_item_table(const char *fp, unsigned length) {
  this->table = new node*[length]; /* allocate table */
  this->length = length; /* set table length */

  for (int i = 0; i < length; ++i) /* 0 out table */
    this->table[i] = NULL;

  ifstream stream; /* start file loading process */
  stream.open(fp); /* load file */
  if (!stream) return; /* only continue if the file exists */

  do {
    CS_item_info tmp(stream);
    if (tmp.is_valid()) /* don't add an empty object */
      this->add_item(tmp);
  } while (!stream.eof()); /* loop until no more to add */

  /* cleanup */
  stream.close();
}


/* deallocate */
CS_item_table::~CS_item_table(void) {
  /* deallocate each chain */
  this->remove_all();

  /* deallocate array */
  delete []this->table;
}


/* add an item to the table */
CS_error CS_item_table::add_item(const CS_item_info &to_add) {
  char *key = to_add.get_name(); /* get a copy of the item's name */
  unsigned hash = this->hash_function(key); /* get hash for item */
  delete []key; /* we don't need the key anymore */

  /* grab old first value */
  node *temp = this->table[hash];

  /* bring in new data */
  this->table[hash] = new node;
  this->table[hash]->data = to_add;
  this->table[hash]->next = temp;

  return SUCCESS;
}


/* remove specific item from the table */
CS_error CS_item_table::remove_item(const char *key) {
  unsigned hash = this->hash_function(key); /* get the hash of the key */
  node *current = this->table[hash], *prev = NULL; /* pointers needed for traversal */

  /* empty chain */
  if (!current)
    return FAILURE;
  else if (current->data == key) { /* first item in chain is a match */
    node *temp = current->next;
    delete this->table[hash];
    this->table[hash] = temp;

    return SUCCESS;
  }

  /* loop through rest of chain */
  while (current) {
    if (current->data == key) { /* use the overloaded equality operator */
      prev->next = current->next; /* delink node and deallocate */
      delete current;

      return SUCCESS;
    }

    /* move forward */
    prev = current;
    current = current->next;
  }

  return FAILURE;
}


/* clear list */
CS_error CS_item_table::remove_all(void) {
  if (!this->table) /* empty table */
    return FAILURE;

  /* loop through all chains */
  for (size_t i = 0; i < this->length; ++i) {
    node *head = this->table[i];

    /* delete everything in each chain */
    while (head) {
      node *temp = head;
      head = head->next;
      delete temp;
    }

    this->table[i] = NULL;
  }

  return SUCCESS;
}


/* retrieve a specific item from the table */
CS_error CS_item_table::retrieve(const char *key, CS_item_info &result) {
  unsigned hash = this->hash_function(key); /* get the hash of the key */
  node *current = this->table[hash]; /* grab the pointer for traversal */

  while (current) { /* traverse */
    if (current->data == key) { /* found a match */
      result = current->data;
      return SUCCESS;
    }

    /* prep for next traversal */
    current = current->next;
  }

  /* if we reach here nothing was found */
  return FAILURE;
}


/* print all chains recursively */
CS_error CS_item_table::print_all(void) const {
  if (!this->table) /* nothing to print */
    return FAILURE;

  /* loop through chains */
  for (int i = 0; i < this->length; ++i) {
    cout << "Chain " << i + 1 << endl; /* print markers */
    cout << "=====================================" << endl;
    print_chain_recurs(this->table[i], true); /* fire off recursive function to print current chain */
  }

  cout << "=====================================" << endl;
}


/* private recursive funciton to print a chain */
void CS_item_table::print_chain_recurs(node *head, bool is_first) const {
  if (!head) /* nothing to print */
    return;

  if (!is_first) /* just for prettier printing */
    cout << endl;

  head->data.print(); /* print data */
  this->print_chain_recurs(head->next, false); /* continue recursive print */
}


/* hahs function used for hashing */
unsigned CS_item_table::hash_function(const char *key) const {
  if (!key || !(*key)) /* nothing to hash - NULL pointer or empty key */
    return 0;

  unsigned hash = 0;
  for (int i = 0; i < strlen(key); ++i)
    hash += i * key[i]; /* hash */

  return hash % this->length; /* wrap to array length */
}

