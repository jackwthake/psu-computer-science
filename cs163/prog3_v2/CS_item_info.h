/*
 * This file holds the declaration for the CS_item_info class, this class holds
 * one item for the scavenger hunt and manages it's members
*/

#ifndef CS_ITEM_INFO_H
#define CS_ITEM_INFO_H

#include "CS_error.h"

#include <fstream>
using namespace std;

class CS_item_info {
  public:
    CS_item_info(void); /* create empty item */
    CS_item_info(ifstream &); /* read item from an already open file stream */
    CS_item_info(char *, char *, char*);
    ~CS_item_info(void); /* deallocate */

    char *get_name() const; /* returns a copy of the item's name */
    CS_error print(void) const; /* print info */
    inline bool is_valid() const { return *this->name; }; /* helper for if object is valid */

    /* overloaded operators */
    void operator=(const CS_item_info &to_copy);
    bool operator==(const char *) const;
  private:
    char *name, *location, *hints;
};

#endif

