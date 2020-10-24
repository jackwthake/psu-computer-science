/*
 * CS_project_list.cpp
 * Jack Thake
 * This file holds all the implementation for the CS_project_list class.
*/

#include "CS_project_list.h"

#include <cstring>
#include <time.h>
#include <iostream>
using namespace std;

/* helper function to convert an int to a time string */
CS_error get_time_val_from_string(const char *t_val, struct tm &when) {
  if (!strptime(t_val, "%m/%d/%y", &when)) {
    return FAILURE;
  }

  return SUCCESS;
};


/* helper function to convert a stringdate to an integer */
CS_error get_time_string_from_int(char *date, struct tm *when) {
  if(!strftime(date, 9, "%m/%d/%y", when)) {
    return FAILURE;
  }

  return SUCCESS;
}


void CS_project::operator=(const CS_project& proj) {
  /* deallocate old strings if they exist */
  if (this->name)
    delete []this->name;
  if (this->workers)
    delete []this->workers;

  /* reallocate */
  this->name = new char[strlen(proj.name) + 1];
  strcpy(this->name, proj.name);
  this->workers = new char[strlen(proj.workers) + 1];
  strcpy(this->workers, proj.workers);

  /* copy over other members */
  this->completion_date = proj.completion_date;
  this->estimated_cost = proj.estimated_cost;
  this->project_length = proj.project_length;
  this->project_coolness = proj.project_coolness;
}


/*
 * Runs at the start of CS_project_list's life - sets up the head pointer
*/
CS_project_list::CS_project_list() {
  this->head = NULL;
}


/*
 * Runs at the end of CS_project_list's life - deallocates all nodes
*/
CS_project_list::~CS_project_list() {
  CS_project_list_node *current = this->head;

  while (current) { /* traverse through list */
    CS_project_list_node *temp = current->next;

    delete current;
    current = temp;
  }

  this->head = NULL;
}


/*
 * Adds one item to the end of the list, returns the CS_error type defined in
 * CS_project.h
*/
CS_error CS_project_list::add_item(CS_project &project) {
  CS_project_list_node *current = this->head;

  /* every project needs a valid name, reject ones without it. */
  if (!project.name)
    return FAILURE;

  if (!this->head) { /* empty list */
    this->head = new CS_project_list_node;
    if (!this->head)
      return MEM_ALLOC_FAIL;

    this->head->data = project;
    this->head->next = NULL;
  } else { /* non-empty list - traverse to end */
    while (current->next) { /* traverse to end of list */
      current = current->next;
    }

    /* create the new node and check memory allocation */
    current->next = new CS_project_list_node;
    if (!current->next)
      return MEM_ALLOC_FAIL;

    /* set data */
    current->next->data = project;
    current->next->next = NULL;
  }

  /* if we reach out here then everything worked. */
  return SUCCESS;
}


/*
 * This function attempts to find and remove a project with a given name,
 * returns FAILURE if none is found, SUCCESS otherwise.
*/
CS_error CS_project_list::remove_item(const char *name) {
  CS_project_list_node *current = this->head, *previous = this->head;

  while (current) { /* traverse the list */
    if (strcmp(name, current->data.name) == 0) { /* check if the current node is a match */
      if (current == this->head) { /* first node */
        this->head = current->next;
      } else { /* middle of the list / end of list */
        previous->next = current->next;
      }

      /* delete and return SUCCESS as we've removed the item. */
      delete current;
      return SUCCESS;
    }

    /* prep for next iteration */
    previous = current;
    current = current->next;
  }

  /* if we get this far then we found no match */
  return FAILURE;
}


/*
 * This function displays all items in a list, if the list is empty - return
 * FAILURE, otherwise return SUCCESS.
*/
CS_error CS_project_list::display(void) const {
  CS_project_list_node *current = this->head;

  /* check for an empty list */
  if (!current)
    return FAILURE;

  while (current) { /* traverse */
    char *date = new char[7];
    get_time_string_from_int(date, &current->data.completion_date);

    cout << "=============================" << endl;
    cout << "Name: " << current->data.name << endl; /* print name atrib */

    if (!current->data.workers) /* print workers atrib (if it exists) */
      cout << "Workers: " << "None" << endl;
    else
      cout << "Workers: " << current->data.workers << endl;

    cout << "Estimated cost: " << current->data.estimated_cost << endl;  /* print cosr atrib */
    cout << "Project Length: " << current->data.project_length << endl;  /* print length atrib */
    cout << "Completion date: " << date << endl;  /* print date atrib */
    cout << "Project Coolness: " << current->data.project_coolness << endl;  /* print coolness atrib */
    cout << "=============================" << endl;

    /* prep for next iteration */
    current = current->next;
  }

  return SUCCESS;
}
