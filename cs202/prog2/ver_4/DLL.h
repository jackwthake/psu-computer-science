#ifndef __DLL_H__
#define __DLL_H__

#include "psu_activity.h"


/*
 * This class represents a node in the DLL
*/
class node {
  public:
    node(void); // default constructor
    node(psu_activity *data); // normal constructor

    /* get next and previous pointers */
    node *get_next(void);
    node *get_prev(void);

    /* set next and previous pointers */
    node *set_next(node *next);
    node *set_prev(node *prev);

    /* return a constant reference to the data */
    const psu_activity &get_data(void);

    /* compare a node directly to an activity */
    bool operator==(const psu_activity *rhs) const;
  private:
    psu_activity *data;
    node *prev, *next;
};


/*
 * Represents an array of DLL
*/
class activity_list {
  public:
    activity_list(void); // we only need a default constructor
    ~activity_list(void); // destructor

    bool add_activity(int priority, psu_activity &to_add); // add an activity to the beginning of a list
    bool remove_activity(psu_activity &to_remove); // search through all priorities for a given activity
    bool get_activity(char *name, psu_activity &result); // return a reference to an activity
    bool clear_all(void); // clear the list
    bool display(void); // print out the list
  private:
    node **head;
};

#endif
