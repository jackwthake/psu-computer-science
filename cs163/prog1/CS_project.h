/*
 * CS_project.h
 * Jack Thake
 * This file holds the structure representing one project
*/

#ifndef CS_PROJECT_H
#define CS_PROJECT_H

#include <time.h>

/* return type for all functions */
typedef enum {
  SUCCESS,
  FAILURE,
  MEM_ALLOC_FAIL
} CS_error;

/* one project in a list */
struct CS_project {
  const char *name;
  const char *workers;
  struct tm completion_date;
  float estimated_cost;
  int project_length;
  int project_coolness;
};

/* helper functions for dealing with dates */
CS_error get_time_val_from_string(const char *t_val, struct tm &when);
CS_error get_time_string_from_int(char *date, struct tm *when);

#endif
