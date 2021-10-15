/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * vehicle.cpp
 *
 * This file contains the definitions for the vehicle class. THe vehicle class is responsible
 * for holding and maintaining a vehicles destination. A vehicle is a child of a the location
 * class, and is the parent of both the plane and ground vehicle class.
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
    vehicle(gate *, float longitude = 0.0f, float latitude = 0.0f); // normal constructor

    // this class manages no dynamic memory, when it goes out of scope - location's deconstructor is automatically invoked.
    
    bool operator==(const vehicle &rhs) const;
  protected:
    /* get and set the destination gate for a given vehicle */
    void set_dest_gate(gate *);
    void get_dest_gate(gate &) const;

  private:
    gate *dest_gate;
};

#endif

