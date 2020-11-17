/*
 * This file holds all implementations for the CS_item_info class, and one static
 * helper function. 
*/

#include "CS_item_info.h"

#include <iostream>
#include <cstring>

/* static helper function to copy a string */
static char *strdup(char *to_dupl) {
  char *res = new char[strlen(to_dupl) + 1]; /* get length */
  if (!res) return NULL; /* check memory was allocated */

  strcpy(res, to_dupl); /* copy data */
  return res; /* return */
}


/* set everything to NULL */
CS_item_info::CS_item_info(void) {
  this->name = this->location = this->hints = NULL;
}


/* read from an already opened input stream */
CS_item_info::CS_item_info(ifstream &stream) {
  char *buf = new char[64]; /* used for each attribute */

  stream.get(buf, 64, '|');
  stream.ignore(100, '|');
  this->name = strdup(buf);

  stream.get(buf, 64, '|');
  stream.ignore(100, '|');
  this->location = strdup(buf);

  stream.get(buf, 64, '|');
  stream.ignore(100, '|');
  this->hints = strdup(buf);
  stream.ignore(100, '\n');

  delete []buf; /* delete buffer */
}


/* deallocate all members */
CS_item_info::~CS_item_info(void) {
  if (this->name)
    delete []this->name;
  if (this->location)
    delete []this->location;
  if (this->hints)
    delete []this->hints;
}


/* print self */
CS_error CS_item_info::print(void) const {
  cout << "Name: " << this->name << "\t Hints: " << this->hints << endl;
  cout << "Location: " << this->location << endl;

  return SUCCESS;
}


/* overloaded assignment operator */
void CS_item_info::operator=(const CS_item_info &to_copy) {
  /* deallocate all old members */
  this->~CS_item_info();
  /* copy each string if they exist */
  if (to_copy.name)
    this->name = strdup(to_copy.name);
  if (to_copy.name)
    this->location = strdup(to_copy.location);
  if (to_copy.name)
    this->hints = strdup(to_copy.hints);
}


/* overloaded equality operator */
bool CS_item_info::operator==(const char *comp) const {
  if (this->name) {
    if (strcmp(this->name, comp) == 0)
      return true;
  }
  return false;
}

