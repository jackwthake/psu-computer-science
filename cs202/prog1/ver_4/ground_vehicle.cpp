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
#include <iostream>
#include "gate.h"


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
    this->set_dest_gate(0);
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


/*
 * Returns if this vehicles is busy or not
*/
bool ground_vehicle::is_busy() const {
  return this->busy;
}


/*
 * prints out the vehicles information
*/
void ground_vehicle::display() const {
  std::cout << "Vehicle Type: ";
  
  if (this->type == refueler)
    std::cout << "refueler" << std::endl;  
  else if (this->type == lavatory)
    std::cout << "lavatory" << std::endl;  
  else if (this->type == air_starter)
    std::cout << "air starter" << std::endl;
  else
   std::cout << "unknown" << std::endl;

  if (this->get_dest_gate()) {
    std::cout << "At gate: " << this->get_dest_gate()->get_identifier() << std::endl; 
  } else {
    std::cout << "Not at a gate" << std::endl;
  }
}

