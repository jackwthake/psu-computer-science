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

#include "vehicle.h"
#include <iostream>
#include "gate.h"


/*
 * default constructor
*/
vehicle::vehicle() : vehicle(NULL) {
  // not needed
}


/* 
 * normal constructor
*/
vehicle::vehicle(gate *dest, float longitude, float latitude) : location(longitude, latitude) {
  this->dest_gate = dest;
}


/*
 * overloaded display function, prints out the vehicle's destination.
*/
void display() {
  std::cout << "Vehicle destination: " << "gate not implemented" << std::endl;
}


/*
 * overloaded equality operator
*/
bool vehicle::operator==(const vehicle &rhs) const {
  if (this->dest_gate == rhs.dest_gate) {
    if (location::operator==(rhs)) {
      return true;
    }
  }

  return false;
}


/*
 * getters and setters
 * both of these are protected member functions.
*/

void vehicle::set_dest_gate(gate *dest) {
  this->dest_gate = dest;
}


void vehicle::get_dest_gate(gate &res) const {
  // TODO: implement after gate class
}

