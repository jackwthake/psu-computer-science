//
//  CS_project.cpp
//  psu-computer-science
//
//  Created by Jack Thake on 13/10/2020.
//  This file holds the definitions for all classes related to the lists
//

#include "CS_project.h"
#include <cstring>
#include <iostream>
using namespace std;

static CS_error copy_string(char *dest, char *src) {
  // TODO: Implement me
  return SUCCESS;
}

/* simple constructor, just calls the other constructor */
CS_project::CS_project() {
  this->name = NULL;
  this->workers = NULL;
  this->completion_date = NULL;
  this->estimated_cost = 0.f;
  this->project_length = 0;
  this->project_coolness = 0;
}


/* main constructor, sets everything up */
CS_project::CS_project(char *name, char *workers, char *comp_date, float cost, int length, int coolness) {
  /* allocate name */
  //copy_string(this->name, name);
  this->name = new char[strlen(name) + 1];
  strcpy(this->name, name);
  /* allocate workers */
  this->workers = new char[strlen(workers) + 1];
  strcpy(this->workers, workers);
  /* allocate completion_date */
  this->completion_date = new char[strlen(comp_date) + 1];
  strcpy(this->completion_date, comp_date);

  this->estimated_cost = cost;
  this->project_length = length;
  this->project_coolness = coolness;
}


/* runs at the end of CS_project's life */
CS_project::~CS_project() {
  if (this->name) /* deallocate name if it exists */
    delete []this->name;
  if (this->workers) /* deallocate workers if it exists */
    delete []this->workers;
  if (this->completion_date) /* deallocate completion date if it exists */
    delete []this->completion_date;
}


/* Print out a project to the user */
CS_error CS_project::display() const {
  /* check if we're a valid object to print */
  if (!this->name && !this->completion_date)
   return FAILURE;

  /* start to print */
  cout << "======================" << endl;
  cout << "Project Name: " << this->name << endl;
  cout << "Project Workers: ";

  /* check that there is memory to print */
  if (!this->workers)
    cout << "None" << endl;
  else
    cout << this->workers << endl;

  cout << "Project Completion Date: " << this->completion_date << endl;
  cout << "Estimated Cost: " << this->estimated_cost << endl;
  cout << "Estimated Project Length: " << this->project_length << endl;
  cout << "Project coolness out of 5:" << this->project_coolness << endl;
  cout << "======================" << endl;

  return SUCCESS;
}


/* performs a deep copy */
void CS_project::operator=(const CS_project& proj) {
  copy_string(this->name, proj.name);
  copy_string(this->workers, proj.workers);
  copy_string(this->completion_date, proj.completion_date);

  this->estimated_cost = proj.estimated_cost;
  this->project_length = proj.estimated_cost;
  this->project_coolness = proj.project_coolness;
}
