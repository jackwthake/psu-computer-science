/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * vehicle.h
 *
 * This file holds the definition for the vehicle class, which inherits from the location class
 * and is the parent to the plane and ground vehicle classes.
*/

#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#include "location.h"

/* this is here solely to stop recursive including */
class gate;

/* vehicle class
 * Represents one vehicle at the airport.
*/
class vehicle : public location {
  public:
    vehicle(); // default constructor
    vehicle(gate &); // normal constructor

    // we don't need a destructor as this class does not manage any dynamic memory.
  protected:
    /* get and set the destination gate for a given vehicle */
    void set_dest_gate(gate &);
    void get_dest_gate(gate &);

  private:
    gate *dest_gate;
};

#endif

