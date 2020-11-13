#include "CS_item_table.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

/* set to 1 for secondary hash function */
#define USE_ALT_HASH 0


/* construct a hash table */
CS_item_table::CS_item_table(size_t length) {
  this->length = length;
  this->table = new node*[length];

  for (size_t i = 0; i < length; ++i)
    *(this->table + i) = NULL;
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

  node *temp = this->table[hash];
  this->table[hash] = new node;
  this->table[hash]->data = to_add;
  this->table[hash]->next = temp;

  free(key);
  return SUCCESS;
}


CS_error CS_item_table::remove_item(const char *key) {
  unsigned hash = hash_function(key);
  node *head = this->table[hash], *prev = NULL;

  if (!head)
    return FAILURE;

  while (head) {
    if (head->data == key) {
      if (!prev) {
        this->table[hash] = head->next;
        delete head;
      } else {
        prev->next = head->next;
        delete head;
      }

      return SUCCESS;
    }

    prev = head;
    head = head->next;
  }

  return FAILURE;
}


CS_error CS_item_table::remove_all(void) {
  if (!this->table)
    return FAILURE;

  for (size_t i = 0; i < this->length; ++i) {
    node *head = this->table[i];

    while (head) {
      node *temp = head;
      head = head->next;
      delete temp;
    }

    this->table[i] = NULL;
  }

  return SUCCESS;
}


CS_error CS_item_table::retrieve(const char *key, CS_item_info &result) const {
  if (!this->table)
    return FAILURE;

  unsigned hash = this->hash_function(key); /* get the hash for the key */
  node *head = this->table[hash];

  while (head) {
    if (head->data == key) {
      result = head->data;
      return SUCCESS;
    }
  }

  return FAILURE;
}


CS_error CS_item_table::display_all(void) const {
  if (!this->table)
    return FAILURE;

  for (size_t i = 0; i < this->length; ++i) {
    cout << "Chain " << i + 1 << endl;
    node *head = this->table[i];

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
  return 0;
}
#endif

