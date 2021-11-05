/*
 * Jack Thake
 * Karla Fant
 * CS202
 * DLL.h
 *
 * This file contains the definitions to the node class and the activity_list class. The node
 * class holds information for an activity as well as links to the previous and next nodes in
 * the DLL. The activity_list class contains an array of doubly linked lists, and holds the 
 * fucntionality needed to interact with the lists.
*/
#ifndef __DLL_H__
#define __DLL_H__

#include "psu_activity.h"

#include <vector>

/*
 * This class represents a node in the DLL
*/
class node {
  public:
    node(void); // default constructor
    node(psu_activity *data); // normal constructor

    /* get next and previous pointers */
    node * &get_next(void);
    node *get_prev(void);

    /* set next and previous pointers */
    void set_next(node *next);
    void set_prev(node *prev);

    /* return a reference to the data */
    psu_activity *get_data(void);

    /* compare a node directly to an activity */
    bool operator==(const psu_activity &rhs) const;
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

    bool add_activity(psu_activity &to_add); // add an activity to the beginning of a list
    bool remove_activity(psu_activity &to_remove, std::vector<class assignment> &completed_assignments); // search through all priorities for a given activity
    psu_activity *get_activity(char *name); // return a reference to an activity
    bool clear_all(void); // clear the list
    bool display(void); // print out the list
  private:
    node **head;

    const int length = 5;
};

#endif
