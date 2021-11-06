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

#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include <string>



/*
 * This Abstract Base Class, will be the parent to the parent to the assignment, remote-assistance
 * and in person_class classes, and will manage the name, priority and time spent attributes.
*/
class psu_activity {
  public:
    /* pure virtual functions for children */
    virtual void display(void) const = 0;
    virtual void prepare(void) = 0;
    virtual void input(void)  = 0;
    virtual void attend(void) = 0;
    
    
    /* getters will be public */
    const char *get_name(void) const;
    int get_priority(void) const;
    int get_time_spent(void) const;

    bool operator==(const psu_activity &rhs) const;
  protected:
    /* protected constructors + destructor, the client should never need to instantiate this class. */
    psu_activity(void);
    psu_activity(const char *name, int priority, int time_spent);
    psu_activity(const psu_activity &);

    ~psu_activity(void);

    /* setters will only be callable by our children */
    void set_name(const char *);
    void set_priority(int);
    void set_time_spent(int);

    int num_prepared, num_attended;
  private:
    char *name;
    int priority, time_spent;
};




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
    void prepare(void) override;

    // we only need getters, there should be no reason to modify an assignment
    std::string get_due_date(void) const;
    bool is_finished(void) const;
    
    /* comparison operator */
    bool operator==(const assignment &rhs);
  private:
    std::string due_date;
    bool finished;
};




/*
 * This class represents one in person class at psu.
*/
class in_person_class : public psu_activity {
  public:
    in_person_class(void); // default constructor
    in_person_class(const char *course_name, const char *teacher, int course_number, int hours_spent, int priority = 1); // normal constructor
    in_person_class(const in_person_class &); // copy constructor

    ~in_person_class(void); // deconstructor

    /* overridden pure virtual functions from the ABT */
    void display(void) const override;
    void input(void) override;
    void attend(void) override;
    void prepare(void) override;

    /* get information, we shouldn't ever need to alter a class */
    const char *get_teacher(void) const;
    int get_course_number(void) const;

    /* comparison operator */
    bool operator==(const in_person_class &rhs);
  private:
    char *teacher;
    int course_number;
};




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
