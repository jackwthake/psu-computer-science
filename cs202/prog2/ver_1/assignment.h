/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * assignment.h
 *
 * This file holds the definition of the assignment class. This class will represent one single assignment, for
 * a given course. assignment is dervied from the ABT psu_activity and will manage two pieces of information, 
 * the assignment's due date as well as weather or not the assignment has been finished or not.
*/

#ifndef __ASSIGNMENT_H__
#define __ASSIGNMENT_H__

#include "psu_activity.h"
#include <string>

/*
 * This class will represent one single assignment for a given course.
*/
class assignment : public psu_activity {
  public:
    assignment(void); // default constructor
    assignment(std::string due_date, const char *name, int time_spent, int priority = 1, bool finsihed = false); // normal constructor

    // overridden virtual functions
    void display(void) const override;
    void input(void) override;
    void attend(void) override;

    // we only need getters, there should be no reason to modify an assignment
    std::string get_due_date(void) const;
    bool is_finished(void) const;
  private:
    std::string due_date;
    bool finished;
};

#endif
