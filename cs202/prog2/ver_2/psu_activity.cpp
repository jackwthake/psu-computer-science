#include "psu_activity.h"

#include <cstring>
#include <cstddef>


psu_activity::psu_activity(void) {
  this->name = NULL;
  this->priority = this->time_spent = 0;
}


psu_activity::psu_activity(const char *name, int priority, int time_spent) {
  if (name) {
    this->name = new char[strlen(name) + 1];
  } else {
    this->name = NULL;
  }

  this->priority = priority;
  this->time_spent = time_spent;
}


psu_activity::psu_activity(const psu_activity &src) {
  delete []this->name;

  psu_activity(src.name, src.priority, src.time_spent);
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
