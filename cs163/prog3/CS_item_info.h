//
//  CS_item_info.h
//  psu-computer-science
//
//  Created by Jack Thake on 11/10/2020.
//  This file holds all declarations for CS_item_info class.
//

#ifndef CS_ITEM_INFO_H
#define CS_ITEM_INFO_H

class CS_item_info {
  public:
    CS_item_info(); /* construct empty item */
    CS_item_info(const char *name, const char *location, const char *hints, const int rating); /* construct populated item */
    ~CS_item_info(); /* deallocate */

    bool print() const; /* print */

    /* overloaded operators */
    void operator=(const CS_item_info &to_copy);
    bool operator==(const CS_item_info &test) const;
  private:
    char *name, *location, *hints;
    int rating;
};

#endif
