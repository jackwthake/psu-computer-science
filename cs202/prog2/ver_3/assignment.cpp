/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * assignment.h
 *
 * This file holds the implementation of the assignment class. This class will represent one single assignment, for
 * a given course. assignment is dervied from the ABT psu_activity and will manage two pieces of information, 
 * the assignment's due date as well as weather or not the assignment has been finished or not.
*/

#include "assignment.h"
#include <iostream>


/*
 * Default Constructor
*/
assignment::assignment(void) : psu_activity() {
  this->due_date = "";
  this->finished = false;  
}


/*
 * Normal Constructor
*/
assignment::assignment(std::string due_date, const char *name, int time_spent, int priority, bool finished) : psu_activity(name, priority, time_spent)  {
  this->due_date = due_date;
  this->finished = finished;
}


/*
 * Overloaded display function
*/
void assignment::display(void) const { 
  if (this->finished) {
    std::cout << "Assignment " << this->get_name() << " was finished and  is due on " << this->due_date << std::endl;
  } else {
    std::cout << "Assignment " << this->get_name() << " is due on " << this->due_date << std::endl;
  }
}


/*
 * Input info into the class
*/
void assignment::input(void) {
  // TODO: Implement me
}


/*
 * this function acts as the function to turn in the assignment, I couldn't come up with a fitting name
 * for all three classes but the functionality is all the same
*/
void assignment::attend(void) {
  this->finished = true;
}


/*
 * Prepare for the assignment
*/
void assignment::prepare(void) {
  std::cout << "Working on assignment " << this->get_name() << std::endl;
}


/*
 * Returns the due date
*/
std::string assignment::get_due_date(void) const {
  return this->due_date;
}


/*
 * return if the assignment is finished
*/
bool assignment::is_finished(void) const {
  return this->finished;
}


/*
 * overloaded comparison operator
*/
bool assignment::operator==(const assignment &rhs) {
  if (this->due_date == rhs.due_date) {
    if (this->finished == rhs.finished) {
      return true;
    }
  }
}

