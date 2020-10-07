/*
 * CS_project_manager.cpp
 * Jack Thake
 * This file holds all the implementation for the CS_project_manager class.
*/

#include "CS_project_manager.h"

#include <iostream>
using namespace std;

/* runs at the start of the manager's life, sets up the head pointer */
CS_project_manager::CS_project_manager() {
  this->head = NULL;
}


/* runs at the end of the manager's life, deallocates everything */
CS_project_manager::~CS_project_manager() {
  CS_project_manager_node *current = this->head;

  while (current) { /* traverse */
    /* hold a temporary pointer to the next node */
    CS_project_manager_node *temp = current->next;
    current->data.~CS_project_list(); /* deallocate node data */

    /* deallocate current node and move to the next */
    delete current;
    current = temp;
  }

  this->head = NULL;
}


/* Adds a new node to the priority list */
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


/* removes a node from the priority list */
CS_error CS_project_manager::remove_priority(int priority) {
  CS_project_manager_node *current = this->head, *previous = this->head;

  while (current) { /* traverse through the list */
    if (current->priority == priority) { /* if we've found a match */
      if (current == head) { /* start of the list */
        head = current->next;
      } else { /* middle / end of list */
        previous->next = current->next;
      }

      /* delete the found node, returning success */
      delete current;
      return SUCCESS;
    }

    /* prep for next iteration */
    previous = current;
    current = current->next;
  }

  return FAILURE;
}


/* add a project to a given priority list */
CS_error CS_project_manager::add_project(int priority, CS_project &project) {
  CS_project_manager_node *current = this->head;

  /* check for empty list */
  if (!this->head)
    return FAILURE;

  while (current) { /* traverse through list */
    if (current->priority == priority) { /* if we've found a match */
      return current->data.add_item(project); /* attempt to add item */
    }

    /* prep for next iteration */
    current = current->next;
  }

  /* if we reach out here, no match was found. */
  return FAILURE;
}


/* remove a project from a priority list, searches for the item */
CS_error CS_project_manager::remove_project(const char *name) {
  CS_project_manager_node *current = this->head;

  /* check for an empty list */
  if (!this->head)
    return FAILURE;

  while (current) { /* traverse */
    /* if the item is successfully removed, exit function */
    if (current->data.remove_item(name) == SUCCESS)
      return SUCCESS;

    /* prep for next iteration */
    current = current->next;
  }

  /* if we reach out here then no match was found */
  return FAILURE;
}


/* lists all items in a given priority */
CS_error CS_project_manager::display_priority(int priority) {
  CS_project_manager_node *current = this->head;

  /* check for an empty list */
  if (!this->head)
    return FAILURE;

  while (current) { /* traverse */
    if (current->priority == priority) /* if we find a match, attempt to print */
      return current->data.display();

    /* prep for next iteration */
    current = current->next;
  }

  /* if we reach out here then we didn't find a match */
  return FAILURE;
}


/* display every project in all priorities */
CS_error CS_project_manager::display_all(void) const {
  CS_project_manager_node *current = this->head;

  /* check for empty list */
  if (!this->head)
    return FAILURE;

  /* traverse through list */
  while (current) {
    cout << "----------------------------" << endl;
    cout << "priority: " << current->priority << endl;
    current->data.display();
    current = current->next;
  }

  return SUCCESS;
}
