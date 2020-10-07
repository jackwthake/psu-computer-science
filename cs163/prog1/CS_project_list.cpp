#include "CS_project_list.h"

#include <cstring>
#include <iostream>
using namespace std;

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


CS_error CS_project_list::remove_item(char *name) {
  CS_project_list_node *current = this->head, *previous = this->head;

  while (current) {
    if (strcmp(name, current->data.name) == 0) {
      if (current == this->head) {
        this->head = current->next;
      } else {
        previous->next = current->next;
      }

      delete current;
      return SUCCESS;
    }

    previous = current;
    current = current->next;
  }

  return FAILURE;
}


CS_error CS_project_list::display(void) const {
  CS_project_list_node *current = this->head;

  if (!current)
    return FAILURE;

  while (current) {
    cout << "=============================" << endl;
    cout << "Name: " << current->data.name << endl;

    if (!current->data.workers)
      cout << "Workers: " << "None" << endl;
    else
      cout << "Workers: " << current->data.workers << endl;

    cout << "Estimated cost: " << current->data.estimated_cost << endl;
    cout << "Project Length: " << current->data.project_length << endl;
    cout << "Completion date: " << current->data.completion_date << endl;
    cout << "Project Coolness: " << current->data.project_coolness << endl;
    cout << "=============================" << endl;
    current = current->next;
  }

  return SUCCESS;
}
