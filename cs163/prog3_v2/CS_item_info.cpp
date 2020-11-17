#include "CS_item_info.h"

#include <iostream>
#include <cstring>

static char *strdup(char *to_dupl) {
  char *res = new char[strlen(to_dupl) + 1];
  if (!res) return NULL;

  strcpy(res, to_dupl);
  return res;
}


CS_item_info::CS_item_info(void) {
  this->name = this->location = this->hints = NULL;
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
  stream.ignore(100, '\n');

  delete []buf;
}


CS_item_info::~CS_item_info(void) {
  if (this->name)
    delete []this->name;
  if (this->location)
    delete []this->location;
  if (this->hints)
    delete []this->hints;
}


CS_error CS_item_info::print(void) const {
  cout << "Name: " << this->name << "\t Hints: " << this->hints << endl;
  cout << "location" << this->location << endl;

  return SUCCESS;
}


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


bool CS_item_info::operator==(const char *) const {
  if (this->name) {
    if (strcmp(this->name, comp) == 0)
      return true;
  }
  return false;
}

