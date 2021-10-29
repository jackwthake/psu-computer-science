/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * psu_activity.h
 *
 * This file holds the definition to the psu_activity class. This class will serve as an
 * Abstract Base Class for the three activities represented in this program. This class's
 * constructors will be protected as their is no reason to ever instantiate this object,
 * all the client will ever need is simply a pointer or reference to an object of this type.
 * The getters are public to aid the client functions working with these classes whiel the
 * getters are only accessible to the children of psu_activity.
*/
#ifndef __PSU_ACTIVITY_H__
#define __PSU_ACTIVITY_H__

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
  private:
    char *name;
    int priority, time_spent;
};

#endif
