#include "CS_item_table.h"

/* set to 1 for secondary hash function */
#define USE_ALT_HASH 0

CS_item_table::CS_item_table(size_t length) {
  this->length = length;
  this->table = new node*[length];

  for (size_t i = 0; i < length; ++i)
    *(this->table + i) = NULL;
}

CS_item_table::~CS_item_table() {
  for (size_t i = 0; i < this->length; ++i) {
    node *head = this->table[i];

    while(head) {
      node *temp = head;
      head = head->next;

      delete temp;
    }
  }
}


CS_error CS_item_table::add_item(const CS_item_info &to_add) {
  const char *key = to_add.get_name();
  unsigned hash = this->hash_function(key);

  node *temp = this->table[hash % this->length];
  this->table[hash % this->length] = new node;
  this->table[hash % this->length]->data = to_add;
  this->table[hash % this->length]->next = temp;

  delete key;
  return SUCCESS;
}


CS_error CS_item_table::remove_item(const char *key) {
  return SUCCESS;
}


CS_error CS_item_table::remove_all(void) {
  return SUCCESS;
}


CS_error CS_item_table::retrieve(const char *key, CS_item_info &result) const {
  return SUCCESS;
}


CS_error CS_item_table::display_all(void) const {
  return SUCCESS;
}


#if USE_ALT_HASH == 0
unsigned CS_item_table::hash_function(const char *key) {
  return 0;
}
#else
unsigned CS_item_table::hash_function(const char *key) {
  return 0;
}
#endif

