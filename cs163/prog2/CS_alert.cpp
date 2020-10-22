#include "CS_alert.h"
#include <cstring>
#include <stdlib.h>
#include <iostream>
using namespace std;

/* creates an empty object */
CS_alert::CS_alert() {
  this->organization = NULL;
  this->date = NULL;
  this->time = NULL;
  this->msg = NULL;
}


/* creates a populated object */
CS_alert::CS_alert(const char *organization, const char *date, const char *time, const char *msg) {
  /* duplicate the passed strings into our memory */
  this->organization = strdup(organization);
  this->date = strdup(date);
  this->time = strdup(time);
  this->msg = strdup(msg);
}


/* deallocates internal strings */
CS_alert::~CS_alert() {
  /* 
   * check if each string is deallocated, if not then deallocate.
   * we are using free becuase strdup uses malloc rather than new, and mixing
   * delete and free causes an error in valgrind 
  */
  if (this->organization)
    free(this->organization);
  if (this->date)
    free(this->date);
  if (this->time)
    free(this->time);
  if (this->msg)
    free(this->msg);
}


/* print message in a formated fashion */
CS_error CS_alert::display() const {
  cout << this->organization << "\t\t" << this->date << " at " << this->time << endl;
  cout << this->msg << endl;

  return SUCCESS;
}


/* overloaded assignment operator, performs a deep copy */
void CS_alert::operator=(const CS_alert &copy) {
  /* 
   * we call our own destructor to minimise code duplication, it'll just
   * deallocate our strings, and then we'll replace them with the copy 
  */
  this->~CS_alert();

  /* duplicate the passed strings into our memory */
  if (copy.organization)
    this->organization = strdup(copy.organization);
  else 
    this->organization = NULL;

  if (copy.date)
    this->date = strdup(copy.date);
  else 
    this->date = NULL;

  if (copy.time)
    this->time = strdup(copy.time);
  else 
    this->time = NULL;

  if (copy.msg)
    this->msg = strdup(copy.msg);
  else 
    this->msg = NULL;
}


/* overloaded operator equal for checking if two alerts are the same */
bool CS_alert::operator==(const CS_alert &test) const {
  /* compare attributes */
  if (strcmp(this->organization, test.organization) == 0) {
    if (strcmp(this->date, test.date) == 0) {
      if (strcmp(this->time, test.time) == 0) {
        if (strcmp(this->msg, test.msg) == 0) {
          return true;
        }
      }
    }
  }

  return false;
}

