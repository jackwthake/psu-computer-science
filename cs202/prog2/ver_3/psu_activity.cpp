/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * psu_activity.cpp
 *
 * This file holds the implementation to the psu_activity class. This class will serve as an
 * Abstract Base Class for the three activities represented in this program. This class's
 * constructors will be protected as their is no reason to ever instantiate this object,
 * all the client will ever need is simply a pointer or reference to an object of this type.
 * The getters are public to aid the client functions working with these classes whiel the
 * getters are only accessible to the children of psu_activity.
*/


#include "psu_activity.h"

#include <cstring>
#include <cstddef>


/*
 * Default constructor
*/
psu_activity::psu_activity(void) {
  this->name = NULL;
  this->priority = this->time_spent = 0;
}


/*
 * normal constructor
*/
psu_activity::psu_activity(const char *name, int priority, int time_spent) : name(NULL) {
  if (name) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
  }

  this->priority = priority;
  this->time_spent = time_spent;
}


/*
 * copy constructor
*/
psu_activity::psu_activity(const psu_activity &src) {
  this->name = NULL;

  if (src.name) {
    this->name = new char[strlen(src.name) + 1];
    strcpy(this->name, src.name);
  }

  this->priority = src.priority;
  this->time_spent = src.time_spent;
}


/*
 * destructor
*/
psu_activity::~psu_activity(void) {
  if (this->name)
    delete []this->name;
}


/*
 * get the actvity's name
*/
const char *psu_activity::get_name(void) const {
  return this->name;
}


/*
 * returns the priority of a given assignment
*/
int psu_activity::get_priority(void) const {
  return this->priority;
}


/*
 * returns the time spent on a given activity in hours
*/
int psu_activity::get_time_spent(void) const {
  return this->time_spent;
}


/*
 * sets the name of the activity
*/
void psu_activity::set_name(const char *name) {
  if (this->name) {
    delete []this->name;
  }

  this->name = new char[strlen(name) + 1];
  strcpy(this->name, name);
}


/*
 * sets the priority for a given assignment
*/
void psu_activity::set_priority(int priority) {
  this->priority = priority; 
}


/*
 * sets the time spent on an activity in hours
*/
void psu_activity::set_time_spent(int time_spent) {
  this->time_spent = time_spent;
}


/*
 * Overloaded equaltiy operator
*/
bool psu_activity::operator==(const psu_activity &rhs) const {
  if (strcmp(this->name, rhs.name) == 0) {
    if (this->priority == rhs.priority && this->time_spent == rhs.time_spent) {
      return true;
    }
  }

  return false;
}

