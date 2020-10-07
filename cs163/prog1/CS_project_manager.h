#ifndef CS_PROJECT_MANAGER_H
#define CS_PROJECT_MANAGER_H

#include "CS_project_list.h"
#include "CS_project.h"

struct CS_project_manager_node {
  int priority;
  CS_project_list data;
  CS_project_manager_node *next;
};

class CS_project_manager {
public:
  CS_project_manager();
  ~CS_project_manager();

  CS_error add_priority(int priority);
  CS_error remove_priority(int priority);

  CS_error add_project(int priority, CS_project &project);
  CS_error remove_project(const char *name);

  CS_error display_priority(int priority);
  CS_error display_all(void) const;
private:
  CS_project_manager_node *head;
};

#endif
