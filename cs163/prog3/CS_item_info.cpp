#include "CS_item_info.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;


CS_item_info::CS_item_info() {
  this->name = NULL;
  this->location = NULL;
  this->hints = NULL;
  this->rating = 0;
}


CS_item_info::CS_item_info(const char *name, const char *location, const char *hints, const int rating) {
  this->name = strdup(name);
  this->location = strdup(location);
  this->hints = strdup(hints);
  this->rating = rating;
}


CS_item_info::~CS_item_info() {
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


bool CS_item_info::print() const {
  if (this->name && this->location && this->hints) {
    cout << this->name << "   Rating: " << this->rating << endl;
    cout << "Hints: " << this->hints << "  Location: " << this->location << endl;

    return true;
  }

  return false;
}


void CS_item_info::operator=(const CS_item_info &to_copy) {
  this->~CS_item_info();
  if (to_copy.name)
    this->name = strdup(to_copy.name);
  if (to_copy.name)
    this->location = strdup(to_copy.location);
  if (to_copy.name)
    this->hints = strdup(to_copy.hints);
  
  this->rating = to_copy.rating;
}


bool CS_item_info::operator==(const CS_item_info &test) const {
  if (!this->name && !test.name)
    return true;

  if (this->name && test.name) {
    if (strcmp(this->name, test.name) == 0)
      return true;
  }

  return false;
}

