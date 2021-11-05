#include "in_person_class.h"

#include <cstddef>
#include <cstring>
#include <iostream>

#include "input.h"

using namespace std;

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

