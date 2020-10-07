/*
 * CS_project.h
 * Jack Thake
 * This file holds the structure representing one project
*/

#ifndef CS_PROJECT_H
#define CS_PROJECT_H

/* return type for all functions */
typedef enum {
  SUCCESS,
  FAILURE,
  MEM_ALLOC_FAIL
} CS_error;

/* one project in a list */
struct CS_project {
  char *name;
  char *workers;
  float estimated_cost;
  int project_length;
  int completion_date;
  int project_coolness;
};

#endif
