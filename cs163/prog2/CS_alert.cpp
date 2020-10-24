#include "CS_alert.h"
#include <cstring>
#include <stdlib.h>
#include <iostream>
using namespace std;


/* CS_alert class */

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


/* CS_alert Class */

/*
 * create the stack, we initialize it with one node rather than just setting
 * head to NULL 
*/
CS_alert_stack::CS_alert_stack() {
  /* set top index */
  this->top = 0;

  /*  create first node */
  this->head = new node;
  this->head->data = new CS_alert[SIZE];
  this->head->next = NULL;
}


/* deallocate all dynamic memory */
CS_alert_stack::~CS_alert_stack() {
  while (this->head) { /* we traverse with head because we delete as we go, no need for a current pointer. */
    node *temp = this->head; /* grab a pointer to the current node */
    this->head = this->head->next; /* set head to next node to not cause any problems with dereferncing NULL pointers */

    /* delete temps data and then the node itself */
    delete []temp->data;
    delete temp;
  }
}


/* push a new alert to the stack, creating a new node if needed */
CS_error CS_alert_stack::push(const CS_alert &to_add) {
  if (top == SIZE) { /* if we've filled the current node */
    node *temp = this->head; /* get a temporary pointer to the old node */

    this->head = new node; /* create the new top of the stack, error checking */
    if (!this->head) { /* if new fails, we return MEM_ALLOC_ERROR and revert to the old stack */
      this->head = temp;
      return MEM_ALLOC_ERROR;
    }

    this->head->data = new CS_alert[SIZE]; /* create new array for the current stack node */
    if (!this->head->data) /* error check allocation */
      return MEM_ALLOC_ERROR;

    /* move the old top node to the second in the list */
    this->head->next = temp;

    /* reset our top index and set our new data */
    this->top = 0;
    this->head->data[this->top] = to_add;
    ++this->top;
  } else { /* there is space in the current node */
    this->head->data[this->top] = to_add; /* bring in new data */
    ++this->top; /* increment our top index */
  }

  return SUCCESS;
}


CS_error CS_alert_stack::pop(void) {
  return SUCCESS;
}


CS_error CS_alert_stack::peak(CS_alert &to_add) const {
  return SUCCESS;
}


/* this function displays the entire stack */
CS_error CS_alert_stack::display(void) const {
  node *current = this->head;

  if (this->top == 0) /* this will only be true if the stack is fully empty */ 
   return FAILURE; 

  while (current) { /* traverse */
    if (current == head) { /* if we're at the top of the stack */
      for (int i = 0; i < this->top; ++i) { /* only loop to our top index as the rest of the array isnt in use. */
        current->data[i].display(); /* display the alert */
        cout << endl; /* padding */
      }
    } else { /* if we're not the head node than we're guarrenteed to be filled so we loop to SIZE */
      for (int i = 0; i < SIZE; ++i) {
        current->data[i].display(); /* display alert */
        cout << endl; /* padding */
      }
    }

    /* prep for next iteration */
    current = current->next;
  }

  return SUCCESS;
}

