/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * remote_assistance.h
 *
 * This file contains the definition to the remote_assistance class. This class is meant to represent
 * one remote assistance session, weather that be office hours, tutoring, etc. This class is derived from
 * the ABT, psu_activity. This class will manage the meeting time, as well as implement all of the pure
 * virtual functions.
*/

#ifndef __REMOTE_ASSISTANCE_H__
#define __REMOTE_ASSISTANCE_H__

#include "psu_activity.h"
#include <string>

/*
 * Represents one remote assistance session
*/
class remote_assistance : public psu_activity {
  public:
    remote_assistance(void); // default constructor
    remote_assistance(std::string meeting_time, std::string meeting_day, const char *name, int time_spent, int priority = 1); // normal constructor

    // overriden virtual functions
    void display(void) const override;
    void input(void) override;
    void attend(void) override;
    void prepare(void) override;

    // unique functions for RTTI
    std::string get_meeting_time(void) const;
    std::string get_meeting_day(void) const;
    bool reschedule_meeting_time(std::string new_time, std::string new_day);

    // comparison operator
    bool operator==(const remote_assistance &rhs);
  private:
    std::string meeting_time;
    std::string meeting_day;
};

#endif