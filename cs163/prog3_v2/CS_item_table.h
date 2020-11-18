#ifndef CS_ITEM_TABLE_H
#define CS_ITEM_TABLE_H

#include "CS_item_info.h"
#include "CS_error.h"

class CS_item_table {
  public:
    CS_item_table(const char *, unsigned length = 7);
    ~CS_item_table(void);

    CS_error add_item(const CS_item_info &);
    CS_error remove_item(const char *);
    CS_error remove_all(void);
    CS_error retrieve(const char *, CS_item_info &);
    CS_error print_all(void) const;
  private:
    struct node {
      CS_item_info data;
      node *next;
    };

    node **table;
    unsigned length;
  private:
    unsigned hash_function(const char *) const;
    void print_chain_recurs(node *, bool) const;
};

#endif
