/*
 * CS_project_list.h
 * Jack Thake
 * This file holds the declarations for the CS_project_list class and the
 * CS_project_list_node struct.
*/

#ifndef CS_PROJECT_LIST_H
#define CS_PROJECT_LIST_H

#include "CS_project.h"

/* one node in the CS_project_list list */
struct CS_project_list_node {
  CS_project data;
  CS_project_list_node *next;
};

/* Represents a list of projects */
class CS_project_list {
public:
  CS_project_list();
  ~CS_project_list();

  CS_error add_item(CS_project &project); /* add item to list */
  CS_error remove_item(char *name); /* remove item from list */
  CS_error display(void) const; /* display list */
private:
  CS_project_list_node *head;
};

#endif
