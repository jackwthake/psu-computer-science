//
//  CS_item_info.cpp
//  psu-computer-science
//
//  Created by Jack Thake on 11/10/2020.
//  This file holds all definitions for CS_item_info class.
//

#include "CS_item_info.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;


/* construct empty item */
CS_item_info::CS_item_info() {
  this->name = NULL;
  this->location = NULL;
  this->hints = NULL;
  this->rating = 0;
}


CS_item_info::CS_item_info(ifstream &stream) {
  char *buf = new char[64];

  stream.get(buf, 64, '|');
  stream.ignore(100, '|');
  this->name = strdup(buf);
  
  stream.get(buf, 64, '|');
  stream.ignore(100, '|');
  this->location = strdup(buf);

  stream.get(buf, 64, '|');
  stream.ignore(100, '|');
  this->hints = strdup(buf);

  stream >> this->rating;
  stream.ignore(100, '\n');

  delete []buf;
}


/* construct complete item */
CS_item_info::CS_item_info(const char *name, const char *location, const char *hints, const int rating) {
  this->name = strdup(name); /* duplicate the strings over */
  this->location = strdup(location);
  this->hints = strdup(hints);
  this->rating = rating;
}


/* delete allocated memory */
CS_item_info::~CS_item_info() {
  /* 
   * I use free rather than delete here because, strdup calls malloc
   * and deleting a malloc region in memory gives an error in Valgrind 
  */
  if (this->name)
    free(this->name);
  if (this->location)
    free(this->location);
  if (this->hints)
    free(this->hints);

  this->name = NULL;
  this->location = NULL;
  this->hints = NULL;
  this->rating = 0;
}


/* print out a formatted version of the item */
bool CS_item_info::print() const {
  if (this->name && this->location && this->hints) {
    cout << this->name << "   Rating: " << this->rating << endl;
    cout << "Hints: " << this->hints << "  Location: " << this->location << endl;

    return true;
  }

  return false;
}


/* overloaded assignment operator */
void CS_item_info::operator=(const CS_item_info &to_copy) {
  /* deallocate our previous memory */
  this->~CS_item_info();

  /* copy each string if they exist */
  if (to_copy.name)
    this->name = strdup(to_copy.name);
  if (to_copy.name)
    this->location = strdup(to_copy.location);
  if (to_copy.name)
    this->hints = strdup(to_copy.hints);
  
  /* bring the rating over */
  this->rating = to_copy.rating;
}


/* overloaded equality operator */
bool CS_item_info::operator==(const CS_item_info &test) const {
  /* if both are NULL, strcmp won't work but they'll be equal */
  if (!this->name && !test.name)
    return true;

  /* only call strcmp if both are allocated */
  if (this->name && test.name) {
    if (strcmp(this->name, test.name) == 0)
      return true;
  }

  /* if we reach here, they are'nt the same */
  return false;
}

    
/* overloaded equality operator for comparing names */
bool CS_item_info::operator==(const char *comp) const {
  if (this->name) {
    if (strcmp(this->name, comp) == 0)
      return true;
  }

  return false;
}


/* return a duplicate copy of the item's name */
char *CS_item_info::get_name() const {
  return strdup(this->name);
}

