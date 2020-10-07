#include "CS_project_manager.h"

#include <iostream>
using namespace std;

CS_project_manager::CS_project_manager() {
  this->head = NULL;
}


CS_project_manager::~CS_project_manager() {
  CS_project_manager_node *current = this->head;

  while (current) {
    CS_project_manager_node *temp = current->next;
    current->data.~CS_project_list();

    delete current;
    current = temp;
  }

  this->head = NULL;
}


CS_error CS_project_manager::add_priority(int priority) {
    CS_project_manager_node *current = this->head;

    if (!head) { /* check for an empty list */
      /* allocate and check for error */
      this->head = new CS_project_manager_node;
      if (!this->head)
        return MEM_ALLOC_FAIL;
      /* set node's values */
      this->head->data = CS_project_list();
      this->head->priority = priority;
      this->head->next = NULL;
    } else { /* populated list, traverse to end */
      /* traverse through the list and check if the priority already exists. */
      while (current->next) {
        if (current->priority == priority)
          return FAILURE;

        current = current->next;
      }
      /* allocate and check for error */
      current->next = new CS_project_manager_node;
      if (!current->next)
        return MEM_ALLOC_FAIL;
      /* set node's values */
      current->next->data = CS_project_list();
      current->next->priority = priority;
      current->next->next = NULL;
    }

    return SUCCESS;
}


CS_error CS_project_manager::remove_priority(int priority) {
  CS_project_manager_node *current = this->head, *previous = this->head;

  while (current) {
    if (current->priority == priority) {
      if (current == head) {
        head = current->next;
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


CS_error CS_project_manager::add_project(int priority, CS_project &project) {
  CS_project_manager_node *current = this->head;

  if (!this->head)
    return FAILURE;

  while (current) {
    if (current->priority == priority) {
      cout << "priority found" << endl;
      return current->data.add_item(project);
    }

    current = current->next;
  }

  return FAILURE;
}


CS_error CS_project_manager::remove_project(const char *name) {
  CS_project_manager_node *current = this->head;

  if (!this->head)
    return FAILURE;

  while (current) {
    if (current->data.remove_item(name) == SUCCESS)
      return SUCCESS;

    current = current->next;
  }

  return FAILURE;
}


CS_error CS_project_manager::display_priority(int priority) {
  CS_project_manager_node *current = this->head;

  if (!this->head)
    return FAILURE;

  while (current) {
    if (current->priority == priority)
      return current->data.display();

    current = current->next;
  }

  return FAILURE;
}


CS_error CS_project_manager::display_all(void) const {
  CS_project_manager_node *current = this->head;

  /* check for empty list */
  if (!this->head)
    return FAILURE;

  /* traverse through list */
  while (current) {
    // TODO: Implement full printing
    cout << current->priority << endl;
    current = current->next;
  }

  return SUCCESS;
}
