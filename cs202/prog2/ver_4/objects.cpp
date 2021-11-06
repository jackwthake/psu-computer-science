/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * objects.h
 *
 * This file contains the definition to all of the objects in this assignment barring
 * the classes related to the DLL. My 3 objects are an assignment, in person class, 
 * and a remote assistance session. The DLL contains all current activities with a 
 * vector containing all finished home work assignments.
*/

#include "objects.h"

#include <cstring>
#include <cstddef>
#include <iostream>

#include "input.h"

using namespace std;


/***********************************************************************************
 * psu_activity class implementation
***********************************************************************************/

/*
 * Default constructor
*/
psu_activity::psu_activity(void) {
  this->name = NULL;
  this->priority = this->time_spent = this->num_prepared = this->num_attended = 0;
}


/*
 * normal constructor
*/
psu_activity::psu_activity(const char *name, int priority, int time_spent) : name(NULL) {
  if (name) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
  }

  this->priority = priority;
  this->time_spent = time_spent;
  this->num_prepared = this->num_attended = 0;
}


/*
 * copy constructor
*/
psu_activity::psu_activity(const psu_activity &src) {
  this->name = NULL;

  if (src.name) {
    this->name = new char[strlen(src.name) + 1];
    strcpy(this->name, src.name);
  }

  this->priority = src.priority;
  this->time_spent = src.time_spent;
  this->num_prepared = src.num_prepared;
  this->num_attended = src.num_attended;
}


/*
 * destructor
*/
psu_activity::~psu_activity(void) {
  if (this->name)
    delete []this->name;
}


/*
 * get the actvity's name
*/
const char *psu_activity::get_name(void) const {
  return this->name;
}


/*
 * returns the priority of a given assignment
*/
int psu_activity::get_priority(void) const {
  return this->priority;
}


/*
 * returns the time spent on a given activity in hours
*/
int psu_activity::get_time_spent(void) const {
  return this->time_spent;
}


/*
 * sets the name of the activity
*/
void psu_activity::set_name(const char *name) {
  if (this->name) {
    delete []this->name;
  }

  this->name = new char[strlen(name) + 1];
  strcpy(this->name, name);
}


/*
 * sets the priority for a given assignment
*/
void psu_activity::set_priority(int priority) {
  this->priority = priority; 
}


/*
 * sets the time spent on an activity in hours
*/
void psu_activity::set_time_spent(int time_spent) {
  this->time_spent = time_spent;
}


/*
 * Output basic info about an activity
*/
void psu_activity::display() const {
  cout << "Activity with name, " << this->name << " and a priority of " << this->priority << " takes " << this->time_spent << "per week" << endl; 
}


/*
 * Input general information about an activity
*/
void psu_activity::input(void) {
  char buf[61];

  /* read in activity name */
  get_input_phrase("Please enter the name of the activity: ", buf, 61);
  /* read in activity priority */
  get_input_int("Please enter the activity's priority (1-10 with 1 being most important): ", this->priority);
  /* read in amount of time */
  get_input_int("Please enter the amount of hours spent per week on this activity: ", this->time_spent);  

  /* set name */
  this->set_name(buf);
}


/*
 * Overloaded equaltiy operator
*/
bool psu_activity::operator==(const psu_activity &rhs) const {
  if (strcmp(this->name, rhs.name) == 0) {
    if (this->priority == rhs.priority && this->time_spent == rhs.time_spent) {
      return true;
    }
  }

  return false;
}




/***********************************************************************************
 * assignment class implementation
***********************************************************************************/


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




/***********************************************************************************
 * in_person_class class implementation
***********************************************************************************/


/*
 * default constructor
*/
in_person_class::in_person_class(void) : psu_activity() {
  this->teacher = NULL;
  this->course_number = 0.f;
}


/*
 * normal constructor
*/
in_person_class::in_person_class(const char *course_name, const char *teacher, int course_number, int hour_spent, int priority) : psu_activity(course_name, priority, hour_spent) {
  if (teacher) {
    this->teacher = new char[strlen(teacher) + 1];
    strcpy(this->teacher, teacher);
  } else {
    this->teacher = NULL;
  }
  
  this->course_number = course_number;
}


/*
 * copy constructor
*/
in_person_class::in_person_class(const in_person_class &src) : psu_activity(src) {
  this->teacher = NULL;

  if (src.teacher) {
    this->teacher = new char[strlen(src.teacher) + 1];
    strcpy(this->teacher, src.teacher);
  }

  this->course_number = src.course_number;
}


/*
 * destructor
*/
in_person_class::~in_person_class(void) {
  if (this->teacher) {
    delete []this->teacher;
  }
}


/*
 * Display the in person class's details
*/
void in_person_class::display(void) const {
  psu_activity::display();

  cout << this->course_number << " is taught by " << this->teacher << endl;    
}


/*
 * Input information into the in person class
*/
void in_person_class::input(void) {
  char buf[21];

  if (this->teacher) {
    delete []this->teacher;
    this->teacher = nullptr;
  }

  psu_activity::input();
  get_input_phrase("Who's the course instructor? ", buf, 21);

  this->teacher = new char[strlen(buf) + 1];
  strcpy(this->teacher, buf);

  get_input_int("What's the course number? ", this->course_number);
}


/*
 * Attend the class
*/
void in_person_class::attend(void) {
  ++this->num_attended;
  cout << "Class " << this->get_name() << " has been attended " << this->num_attended << " time(s)." << endl;
}


/*
 * Prepare for the class
*/
void in_person_class::prepare(void) {
  ++this->num_prepared;
  cout << "Class " << this->get_name() << " has been practiced  " << this->num_prepared << " time(s)." << endl;
}


/*
 * Return the teacher in a read-only version
*/
const char *in_person_class::get_teacher(void) const {
  return this->teacher;
}


/*
 * returns a copy of the course number
*/
int in_person_class::get_course_number(void) const {
  return this->course_number;
}


/*
 * comparison operator
*/
bool in_person_class::operator==(const in_person_class &rhs) {
  if (this->course_number == rhs.course_number) {
    if (strcmp(this->teacher, rhs.teacher) == 0) {
      if (psu_activity::operator==(rhs)) {
        return true;
      }
    }
  }

  return false;
}




/***********************************************************************************
 * remote_assistance class implementation
***********************************************************************************/


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

