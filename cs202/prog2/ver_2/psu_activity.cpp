#include "psu_activity.h"

#include <cstring>
#include <cstddef>


psu_activity::psu_activity(void) {
  this->name = NULL;
  this->priority = this->time_spent = 0;
}


psu_activity::psu_activity(const char *name, int priority, int time_spent) : name(NULL) {
  if (name) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
  }

  this->priority = priority;
  this->time_spent = time_spent;
}


psu_activity::psu_activity(const psu_activity &src) {
  this->name = NULL;

  if (src.name) {
    this->name = new char[strlen(src.name) + 1];
    strcpy(this->name, src.name);
  }

  this->priority = src.priority;
  this->time_spent = src.time_spent;
}


psu_activity::~psu_activity(void) {
  if (this->name)
    delete []this->name;
}


const char *psu_activity::get_name(void) const { }
int psu_activity::get_priority(void) const { }
int psu_activity::get_time_spent(void) const { }

void psu_activity::set_name(const char *) { }
void psu_activity::set_priority(int) { }
void psu_activity::set_time_spent(int) { }
