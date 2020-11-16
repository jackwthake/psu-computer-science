//
//  CS_item_table.h
//  psu-computer-science
//
//  Created by Jack Thake on 11/12/2020.
//  This file holds the declarations for the CS_item_table class
//

#ifndef CS_ITEM_TABLE_H
#define CS_ITEM_TABLE_H

#include <cstddef>
#include <fstream>

#include "CS_item_info.h"
#include "CS_error.h"
using namespace std;

class CS_item_table {
  public:
    CS_item_table(ifstream &stream, size_t length = 13);
    ~CS_item_table();

    CS_error add_item(const CS_item_info &);
    CS_error remove_item(const char *key);
    CS_error remove_all(void);

    CS_error retrieve(const char *key, CS_item_info &) const;
    CS_error display_all(void) const;
  private:
    unsigned hash_function(const char *) const;
  private:
    struct node {
      CS_item_info data;
      node *next;
    };

    node **table;
    size_t length;
};

#endif
