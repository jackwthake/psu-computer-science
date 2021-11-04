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

#include "input.h"

using namespace std;

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
  psu_activity::display();

  if (this->finished) {
    cout << "This assignment for has already been turned in." << endl;
  } else {
    cout << "This assignment is due on " << this->due_date << endl;
  }
}


/*
 * Input info into the class
*/
void assignment::input(void) {
  psu_activity::input();
  char buf[21];

  get_input_phrase("Please enter the assignment's due date (mm/dd/yy): ", buf, 21);
  this->due_date = buf; 
}


/*
 * this function acts as the function to turn in the assignment, I couldn't come up with a fitting name
 * for all three classes but the functionality is all the same
*/
void assignment::attend(void) {
  if (!this->finished) {
    ++this->num_attended;
    this->finished = true;
    
    cout << "Assignemnt " << this->get_name() << " has been turned in." << endl;
  } else {
    cout << "Assignemnt " << this->get_name() << " was already turned in." << endl;
  }
}


/*
 * Prepare for the assignment
*/
void assignment::prepare(void) {
  ++this->num_prepared;
  cout << "Class " << this->get_name() << " has been worked on ` " << this->num_prepared << " time(s)." << endl;
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
      if (psu_activity::operator==(rhs)) {
        return true;
      }
    }
  }

  return false;
}

