/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * in_person_class.h
 *
 * This file holds the definition for the in_person_class class. This class will represent one in course at
 * PSU that meets in person. in_person_class is a child of psu_activity which is an ABT, meaning in_person_class
 * will have to implement all of th epure virtual functions it inherits. This class will manage the name of the 
 * teacher associated with the course as well as the course number.
*/

#ifndef __IN_PERSON_CLASS_H__
#define __IN_PERSON_CLASS_H__

#include "psu_activity.h"

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

#endif
