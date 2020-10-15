//
//  CS_project.h
//  psu-computer-science
//
//  Created by Jack Thake on 13/10/2020.
//  This file holds all declaration for list class
//

#ifndef CS_project_h
#define CS_project_h

/* use to denote error or success type */
typedef enum {
  SUCCESS,
  FAILURE,
  MEM_ALLOC_FAIL
} CS_error;


/* holds all info regarding one project, manages it's memory */
class CS_project {
public:
    CS_project();
    CS_project(char *name, char *workers, char *comp_date, float cost, int length, int coolness);
    ~CS_project();

    CS_error display() const; /* display object */
    bool is_match(char *test); /* check if nmaes match */
    void operator=(const CS_project& proj); /* assignment operator */
private:
  char *name, *workers, *completion_date;
  float estimated_cost;
  int project_length, project_coolness;
};


/* contains functionality for one list of projects */
class CS_project_list {
public:
  CS_project_list();
  ~CS_project_list();

  CS_error add_project(const CS_project &project); /* add project to list */
  CS_error remove_project(char *to_remove); /* remove project from list */
  CS_error display() const; /* display list */
private:
  struct node {
    CS_project project;
    node *next;
  };

  node *head;
};


/* contains all functionality for one list of lists */
class CS_project_manager {
public:
  CS_project_manager();
  ~CS_project_manager();

  CS_error add_priority(const int &to_add); /* add priority list */
  CS_error remove_priority(const int &to_remove); /* remove priority list */

  CS_error add_project(const int &priority, const CS_project &project); /* add project to a given list */
  CS_error remove_project(char *to_remove); /* search and remove */

  CS_error display() const; /* display all lists */
  CS_error display(const int &priority) const; /* display one priority list*/
private:
  bool does_exist(const int &priority) const; /* check if a priority already exists */

  struct node {
    CS_project_list list;
    int priority;
    node *next;
  };

  node *head;
};

#endif /* CS_project_h */
