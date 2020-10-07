#include "CS_project_list.h"

#include <iostream>
using namespace std;

CS_project_list::CS_project_list() {
  this->head = NULL;
}


CS_project_list::~CS_project_list() {
  // TODO: Implement this
}

/*
 * Adds one item to the end of the list, returns the CS_error type defined in
 * CS_project.h
*/
CS_error CS_project_list::add_item(CS_project &project) {
  CS_project_list_node *current = this->head;

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
  // TODO: Implement this
  return SUCCESS;
}


CS_error CS_project_list::display(void) const {
  CS_project_list_node *current = this->head;

  if (!current)
    return FAILURE;

  while (current) {
    // TODO: print project info
    cout << "Item" << endl;
    current = current->next;
  }

  return SUCCESS;
}
