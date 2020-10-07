/*
 * CS_project_manager.h
 * Jack Thake
 * This file holds the declarations for the CS_project_manager class and the
 * CS_project_manager_node struct.
*/

#ifndef CS_PROJECT_MANAGER_H
#define CS_PROJECT_MANAGER_H

#include "CS_project_list.h"
#include "CS_project.h"

/* represents one node in CS_project_manager's list */
struct CS_project_manager_node {
  int priority;
  CS_project_list data;
  CS_project_manager_node *next;
};

/* represents a list of prioritized projects */
class CS_project_manager {
public:
  CS_project_manager();
  ~CS_project_manager();

  CS_error add_priority(int priority); /* add priority list */
  CS_error remove_priority(int priority); /* remove priority list */

  CS_error add_project(int priority, CS_project &project); /* add project to given list */
  CS_error remove_project(const char *name); /* remove a project */

  CS_error display_priority(int priority); /* display one priority list */
  CS_error display_all(void) const; /* display all projects in all priorities */
private:
  CS_project_manager_node *head;
};

#endif
