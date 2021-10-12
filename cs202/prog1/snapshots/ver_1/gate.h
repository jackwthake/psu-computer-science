/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * gate.h
 *
 * This file contains the definitions for the node class and the gate class
*/
#ifndef __GATE_H__
#define __GATE_H__

#include "location.h"
#include "plane.h"


/* 
 * represents one node in the gate's qeue (LLL)
*/
class node : public plane {
  public:
    node(); /* default constructor */
    node(const plane &data); /* normal constructor */

    node *get_next(); /* get the next node in the list */
    void set_next(node *); /* set the next node in the list */

  private:
    node *next;
};


/* 
 * Represents one gate at the airport, Responsible for managing a qeue of future arrivals
 * and communicating with both the currently landed flight, as well as the ground vehicles.
*/
class gate : public location {
  public:
    gate(); // default constructor
    gate(char *identifier); // normal constructor
    gate(const gate &); // copy constructor

    ~gate();

    bool enqeue_flight(const plane &); // add a flight to the qeue
    bool deqeue_flight(int flight_id); // remove a flight from the qeue
    bool clear_flight_qeue(); // clear list

    const plane &get_flight_info(int flight_id) const; // retrieve a flight from the list
  private:
    void upon_landing(); // handler function for when a plane lands

    node *head;
};

#endif

