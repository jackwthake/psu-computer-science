/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * scheduler.h
 *
 * This file contains the declarations to the scheduler class and it's node class.
 * scheduler contains both a BST of all available events and a list of all currently
 * scheduled events, as well as various operators to deal with them.
*/

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "events.h"
  

/* representss a node in scheduler's BST */
class node {
  public:
    node();
    node(event *data);

    /* get left and right nodes */
    node * &get_right();
    node * &get_left();

    /* set left and right nodes */
    void set_right(node *right);
    void set_left(node *left);

    /* get the data in a node */
    event *get_data();
  private:
    event *data;
    node *left, *right;
};



/* Contains a bst of all available events and a list of all scheduled ones */
class scheduler {
  public:
    /* constructors + destructors */
    scheduler();
    scheduler(const scheduler &);

    ~scheduler();

    /* add events to the collections */
    bool add_event(event *to_add);
    bool schedule_event(const char *name);

    /* get events from the collections */
    event *get_event_details(const char *name);
    event *get_scheduled_event(const char *name);

    /* remove items from the collections */
    bool remove_event(const char *name);
    bool unschedule_event(const char *name);
    
    /* clear the collections */
    bool clear_scheduled();
    bool clear_events();

    /* display */
    bool display_all_events() const;
    bool display_scheduled_events() const;

    /* overloaded operators */
    void operator=(const scheduler &);
    bool operator==(const scheduler &) const;
    bool operator!=(const scheduler &) const;

    scheduler &operator+=(const event &); // will add an event into the BST
    scheduler &operator-=(const event &); // will remove an event from the BST

    friend scheduler &operator+(const scheduler &a, const scheduler &b); /* add two scheduler objects together, combining their lists */
    friend scheduler &operator-(const scheduler &a, const scheduler &b); /* subtract two pettting objects from eachother, removing their matching list elements */
  private:
    std::list<event *>scheduled; // contains a list of all scheduled events
    node *root; // contains a BST of all events
};


#endif
