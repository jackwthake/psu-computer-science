#include "CS_item_table.h"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

CS_item_table::CS_item_table(const char *fp, unsigned length) {
  this->table = new node*[length];
  this->length = length;

  for (int i = 0; i < length; ++i)
    this->table[i] = NULL;

  ifstream stream;
  stream.open(fp);
  if (!stream) return;

  do {
    CS_item_info tmp(stream);
    if (tmp.is_valid())
      this->add_item(tmp);
  } while (!stream.eof());
}

CS_item_table::~CS_item_table(void) {
  /* deallocate each chain */
  this->remove_all();

  /* deallocate array */
  delete []this->table;
}

CS_error CS_item_table::add_item(const CS_item_info &to_add) {
  char *key = to_add.get_name();
  unsigned hash = this->hash_function(key);
  delete []key;

  node *temp = this->table[hash];

  this->table[hash] = new node;
  this->table[hash]->data = to_add;
  this->table[hash]->next = temp;

  return SUCCESS;
}


CS_error CS_item_table::remove_item(const char *key) {
  unsigned hash = this->hash_function(key);
  node *current = this->table[hash], *prev = NULL;

  if (!current)
    return FAILURE;
  else if (current->data == key) {
    node *temp = current;
    current = current->next;
    delete temp;

    return SUCCESS;
  }

  while (current) {
    if (current->data == key) {
      prev->next = current->next;
      delete current;

      return SUCCESS;
    }

    prev = current;
    current = current->next;
  }

  return FAILURE;
}


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


CS_error CS_item_table::retrieve(const char *key, CS_item_info &result) {
  unsigned hash = this->hash_function(key);
  node *current = this->table[hash];

  while (current) {
    if (current->data == key) {
      result = current->data;
      return SUCCESS;
    }

    current = current->next;
  }

  return FAILURE;
}


CS_error CS_item_table::print_all(void) const {
  if (!this->table)
    return FAILURE;

  for (int i = 0; i < this->length; ++i) {
    cout << "Chain " << i + 1 << endl;
    cout << "=====================================" << endl;
    print_chain_recurs(this->table[i], true);
  }

  cout << "=====================================" << endl;
}

void CS_item_table::print_chain_recurs(node *head, bool is_first) const {
  if (!head)
    return;

  if (!is_first)
    cout << endl;

  head->data.print();
  this->print_chain_recurs(head->next, false);
}

unsigned CS_item_table::hash_function(const char *key) const {
  if (!key || !(*key))
    return 0;

  unsigned hash = 0;
  for (int i = 0; i < strlen(key); ++i)
    hash += i * key[i];

  return hash % this->length;
}
