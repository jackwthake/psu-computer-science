/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * ground_vehicle.cpp
 *
 * This file contains the defintions for the ground_vehicle class. the ground vehicle class
 * manages it's state, wether it's busy or not, as well as it's detsination gate. the ground
 * vehicle class inherits from the vehicle class and is the parent of the v_node class
 */

#include "ground_vehicle.h"


/*
 * default constructor
*/
ground_vehicle::ground_vehicle() : ground_vehicle(unknown) {
 // not needed
}


/*
 * normal constructor
*/
ground_vehicle::ground_vehicle(vehicle_type type, float longitude, float latitude, bool busy) : vehicle(0, longitude, latitude) {
  this->type = type;
  this->busy = false;
}


/*
 * overloaded operator equals
*/
bool ground_vehicle::operator==(const ground_vehicle &rhs) {
  if (this->type == rhs.type && this->busy == rhs.busy) {
    if (vehicle::operator==(rhs)) {
      return true;
    }
  }

  return false;
}


/*
 * requests the vehicle to go to a given gate, if the vehicle is free then it will, otherwise the
 * function will fail and return false.
*/
bool ground_vehicle::request(gate *dest) {
  if (!this->busy) {
    this->set_dest_gate(dest);
    this->busy = true;

    return true;
  }

  return false;
}


/*
 * release the vehicle from a gate, the function will fail and return negative
 * if the vehicle is not actually busy.
*/
bool ground_vehicle::release() {
  if (this->busy) {
    this->set_dest_gate(nullptr);
    this->busy = false;

    return false;
  }

  return true;
} 


/* 
 * returns the type of the vehicle
*/
vehicle_type ground_vehicle::get_type() const {
  return this->type;
}

