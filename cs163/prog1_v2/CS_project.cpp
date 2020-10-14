//
//  CS_project.cpp
//  psu-computer-science
//
//  Created by Jack Thake on 13/10/2020.
//  This file holds the definitions for all classes related to the lists. In 
//  this file I use free rather than delete [], and theres a reason for that:
//  strdup calls malloc and using delete [] on a malloc'd region of memory
//  causes valgrind to spew errors about mismatching free and delete. please
//  don't mark me down for that.
//

#include "CS_project.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;


/*********************************
 * CS_project class functions
**********************************/

/* simple constructor, just calls the other constructor */
CS_project::CS_project() {
  this->name = NULL;
  this->workers = NULL;
  this->completion_date = NULL;
  this->estimated_cost = 0.f;
  this->project_length = 0;
  this->project_coolness = 0;
}


/* main constructor, sets everything up */
CS_project::CS_project(char *name, char *workers, char *comp_date, float cost, int length, int coolness) {
  /* allocate name */
  //copy_string(this->name, name);
  this->name = strdup(name);
  /* allocate workers */
  this->workers = strdup(workers);
  /* allocate completion_date */
  this->completion_date = strdup(comp_date);

  this->estimated_cost = cost;
  this->project_length = length;
  this->project_coolness = coolness;
}


/* runs at the end of CS_project's life */
CS_project::~CS_project() {
  if (this->name) /* deallocate name if it exists */
    free(this->name);
  if (this->workers) /* deallocate workers if it exists */
    free(this->workers);
  if (this->completion_date) /* deallocate completion date if it exists */
    free(this->completion_date);
}


/* Print out a project to the user */
CS_error CS_project::display() const {
  /* check if we're a valid object to print */
  if (!this->name && !this->completion_date)
   return FAILURE;

  /* start to print */
  cout << "======================" << endl;
  cout << "Project Name: " << this->name << endl;
  cout << "Project Workers: ";

  /* check that there is memory to print */
  if (!this->workers)
    cout << "None" << endl;
  else
    cout << this->workers << endl;

  cout << "Project Completion Date: " << this->completion_date << endl;
  cout << "Estimated Cost: " << this->estimated_cost << endl;
  cout << "Estimated Project Length: " << this->project_length << endl;
  cout << "Project coolness out of 5: " << this->project_coolness << endl;
  cout << "======================" << endl;

  return SUCCESS;
}


bool CS_project::is_match(char *test) {
  if (strcmp(this->name, test) == 0)
    return true;

  return false;
}


/* performs a deep copy */
void CS_project::operator=(const CS_project& proj) {
  /* deallocate old strings if they exist */
  if (this->name)
    free(this->name);
  if (this->workers)
    free(this->workers);
  if (this->completion_date)
    free(this->completion_date);

  /* strdup creates a duplicate of a given string use `man strdup` */
  if (proj.name) /* check to make sure theres a string to copy */
    this->name = strdup(proj.name);
  else /* if theres no string to copy, we've already free'd the memory so set to NULL */
    this->name = NULL;

  if (proj.workers) /* check to make sure theres a string to copy */
    this->workers = strdup(proj.workers);
  else /* if theres no string to copy, we've already free'd the memory so set to NULL */
    this->workers = NULL;

  if (proj.completion_date) /* check to make sure theres a string to copy */
    this->completion_date = strdup(proj.completion_date);
  else /* if theres no string to copy, we've already free'd the memory so set to NULL */
    this->completion_date = NULL;

  /* copy over non dynamic values */
  this->estimated_cost = proj.estimated_cost;
  this->project_length = proj.estimated_cost;
  this->project_coolness = proj.project_coolness;
}



/*********************************
 * CS_project_list class functions
**********************************/

/* sets up head pointer */
CS_project_list::CS_project_list() {
  this->head = NULL;
}


/* deallocates all list items, and their projects */
CS_project_list::~CS_project_list() {
  while(this->head) {
    node *tmp = this->head;
    this->head = this->head->next;
    delete tmp;
  }
}


/* add project to list */
CS_error CS_project_list::add_project(const CS_project &project) {
  node *tmp = this->head;

  this->head = new node;
  if (!this->head) { /* if allocation fails, revert back and return MEM_ALLOC_FAIL */
    this->head = tmp;
    return MEM_ALLOC_FAIL;
  }

  /* use the overloaded operator = */
  this->head->project = project;
  this->head->next = tmp;

  return SUCCESS;
}


/* remove a project from the list assuming it exists */
CS_error CS_project_list::remove_project(char *to_remove) {
  node *current = this->head, *previous = this->head;

  while (current) {
    if (current->project.is_match(to_remove)) { /* check if we've found a match */
      if (current == this->head) /* rearrange nodes depends on position in the list */
        this->head = current->next;
      else
        previous->next = current->next;

      /* after we rearrange, we cna delete and return */
      delete current;
      return SUCCESS;
    }

    /* prep for next iteration */
    current = current->next;
  }

  /* if we reach out here then we never found a match */
  return FAILURE;
}


/* lists all items in the list */
CS_error CS_project_list::display() {
  node *current = this->head;
  bool has_failed = false;

  if (!this->head) /* check for an empty list */
    return FAILURE;

  while (current) {
    if (!current->project.display()) /* display and error check */
      has_failed = true;

    /* prep for next line */
    current = current->next;
  }

  /* check if an iteration failed */
  if (has_failed)
    return FAILURE;

  return SUCCESS;
}

