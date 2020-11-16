//
//  CS_item_table.cpp
//  psu-computer-science
//
//  Created by Jack Thake on 11/12/2020.
//  This file holds the implementation for the CS_item_table class
//

#include "CS_item_table.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

/* set to 1 for secondary hash function */
#define USE_ALT_HASH 0


/* construct a hash table */
CS_item_table::CS_item_table(ifstream &stream, size_t length) {
  this->length = length;
  this->table = new node*[length];

  for (size_t i = 0; i < length; ++i)
    *(this->table + i) = NULL;

  if (stream) {
    while (!stream.eof()) {
      CS_item_info tmp(stream);
      this->add_item(tmp);
    }  
  }
}


/* deallocate all memory, for each array */
CS_item_table::~CS_item_table() {
  /* deallocate each chain */
  this->remove_all();

  /* deallocate array */
  delete []this->table;
}


/* add item to hash table */
CS_error CS_item_table::add_item(const CS_item_info &to_add) {
  char *key = to_add.get_name(); /* get the key */
  unsigned hash = this->hash_function(key); /* get the hash for the key */

  /* allocate new node */
  node *temp = this->table[hash];
  this->table[hash] = new node;
  this->table[hash]->data = to_add;
  this->table[hash]->next = temp;

  /* free the key, we use free because strdup calls malloc. */
  free(key);
  return SUCCESS;
}


CS_error CS_item_table::remove_item(const char *key) {
  unsigned hash = hash_function(key); /* get the hash */
  node *head = this->table[hash], *prev = NULL;

  /* empty list */
  if (!head)
    return FAILURE;

  while (head) { /* traverse */
    if (head->data == key) { /* match found */
      if (!prev) { /* first item in list */
        this->table[hash] = head->next;
        delete head;
      } else { /* middle of list */
        prev->next = head->next;
        delete head;
      }

      /* we deleted a node */
      return SUCCESS;
    }

    /* prepare for next iteration */
    prev = head;
    head = head->next;
  }

  /* if we reach out here then nothing was removed */
  return FAILURE;
}


/* Delete all items in the table, deallocating memory */
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


/* retrieve an item based on it's key  */
CS_error CS_item_table::retrieve(const char *key, CS_item_info &result) const {
  if (!this->table) /* no table */
    return FAILURE;

  /* get the hash */
  unsigned hash = this->hash_function(key); /* get the hash for the key */
  node *head = this->table[hash];

  /* loop through the chain */
  while (head) {
    if (head->data == key) { /* use the overloaded operator equals, compare with string */
      result = head->data;
      return SUCCESS;
    }
  }

  /* if we reach here, nothing was found */
  return FAILURE;
}


/* display all in the table */
CS_error CS_item_table::display_all(void) const {
  if (!this->table) /* no table */
    return FAILURE;

  /* loop through all chains */
  for (size_t i = 0; i < this->length; ++i) {
    cout << "Chain " << i + 1 << endl; /* display chain number */
    node *head = this->table[i];

    /* traverse through the chain, printing thier values */
    while (head) {
      cout << "---------------------------------" << endl;
      head->data.print();

      head = head->next;
    }

    cout << "---------------------------------" << endl;
  }

  return SUCCESS;
}


#if USE_ALT_HASH == 0
unsigned CS_item_table::hash_function(const char *key) const {
  unsigned hash = 0;
  for (size_t i = 0; i < strlen(key); ++i)
    hash += i * key[i];

  return hash % this->length;
}
#else
unsigned CS_item_table::hash_function(const char *key) {
  unsigned hash = 0;
  for (size_t i = 0; i < strlen(key); ++i)
    hash += key[i];

  return hash % this->length;
}
#endif

