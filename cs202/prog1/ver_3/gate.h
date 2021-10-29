/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * gate.h
 *
 * This file contains the definitions for the p_node class and the gate class
*/
#ifndef __GATE_H__
#define __GATE_H__

#include "location.h"
#include "plane.h"
#include "vehicle_manager.h"


/* 
 * represents one node in the gate's qeue (LLL)
*/
class p_node : public plane {
  public:
    p_node(); /* default constructor */
    p_node(const plane &data); /* normal constructor */
    p_node(const p_node &src); /* copy constructor */

    p_node *get_next(); /* get the next p_node in the list */
    void set_next(p_node *); /* set the next p_node in the list */

  private:
    p_node *next;
};


/* 
 * Represents one gate at the airport, Responsible for managing a qeue of future arrivals
 * and communicating with both the currently landed flight, as well as the ground vehicles.
*/
class gate : public location {
  public:
    gate(); // default constructor
    gate(char *identifier, float longitude = 0.f, float latitudei = 0.f); // normal constructor
    gate(const gate &); // copy constructor

    ~gate();

    bool enqeue_flight(const plane &); // add a flight to the qeue
    bool deqeue_flight(int flight_id); // remove a flight from the qeue
    bool clear_flight_queue(); // clear list

    const plane &get_flight_info(int flight_id) const; // retrieve a flight from the list
  private:
    void upon_landing(const vehicle_manager &); // handler function for when a plane lands

    /* recursive fucntion to find a given flight in the qeue */
    const plane &get_flight_info(int flight_id, p_node *head);
    p_node *copy_list(p_node *head, p_node *src);

    char *identifier;
    p_node *head;
};

#endif
