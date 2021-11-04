/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * remote_assistance.h
 *
 * This file contains the implementation to the remote_assistance class. This class is meant to represent
 * one remote assistance session, weather that be office hours, tutoring, etc. This class is derived from
 * the ABT, psu_activity. This class will manage the meeting time, as well as implement all of the pure
 * virtual functions.
*/

#include "remote_assistance.h"

#include <iostream>

#include "input.h"

using namespace std;

/*
 * Default constructor
*/
remote_assistance::remote_assistance(void) : psu_activity() {
  this->meeting_time = "";
  this->meeting_day = "";
}


/*
 * Normal constructor
*/
remote_assistance::remote_assistance(string meeting_time, string meeting_day, const char *name, int time_spent, int priority) : psu_activity(name, priority, time_spent) {
  this->meeting_time = meeting_time;
  this->meeting_day = meeting_day;
}


/*
 * display the basic info about the class
*/
void remote_assistance::display(void) const {
  psu_activity::display();

  cout << "Remote Session is scheduled on " << this->meeting_day << " at " << this->meeting_time << endl;
}


/*
 * Input general information into the class
*/
void remote_assistance::input(void) {
  char buf[31];

  psu_activity::input();

  get_input_phrase("Please enter the remote session's meeting day (M for monday or M/F for monday and friday): ", buf, 31);
  this->meeting_day = buf;

  memset(buf, 0x00, 31);

  get_input_phrase("Please enter the remote session's meeting time (12:00pm): ", buf, 31);
  this->meeting_time = buf;
}


/*
 * Attend the remote assistance session and increment the counter
*/
void remote_assistance::attend(void) {
  ++this->num_attended;
  cout << "Remote session with name " << this->get_name() << " has been attended " << this->num_attended << " time(s)." << endl;
}


/*
 * Prepare for the remote assistance session
*/
void remote_assistance::prepare(void) {
  ++this->num_prepared;
  cout << "Remote session with name " << this->get_name() << " has been prepared for " << this->num_attended << " time(s)." << endl;
}


/* 
 * returns a copy of the meeting day
*/
std::string remote_assistance::get_meeting_day(void) const {
  return this->meeting_day;
}


/*
 * returns a copy of the meeting time
*/
std::string remote_assistance::get_meeting_time(void) const {
  return this->meeting_time;
}


/*
 * reschedule the meeting time and day
*/
bool remote_assistance::reschedule_meeting_time(string new_time, string new_day) {
  this->meeting_time = new_time;
  this->meeting_day = new_day;

  if ((this->meeting_time != new_time) || (this->meeting_day != new_day))
    return false;

  return true;
}


/*
 * Overloaded equality operator
*/
bool remote_assistance::operator==(const remote_assistance &rhs) {
  if (this->meeting_time == rhs.meeting_time && this->meeting_day == rhs.meeting_day) {
    if (psu_activity::operator==(rhs)) {
      return true;
    }
  }

  return false;
}

