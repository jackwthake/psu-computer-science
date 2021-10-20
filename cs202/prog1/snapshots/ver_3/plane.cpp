/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * plane.cpp
 *
 * This file contains the definition for the plane class. The plane class is responsible for
 * managing information regarding a given flight. A plane is a child of a vehicle, and is the 
 * parent to the p_node class.
*/

#include "plane.h"


/*
 * Default Constructor
*/
plane::plane() : plane(nullptr, "", 0, 0) {
  // not needed
}


/*
 * Normal Constructor
*/
plane::plane(gate *dest_gate, std::string dep_from, int flight_num, int num_passengers, bool landed) : vehicle(dest_gate) {
  this->dep_from = dep_from;
  this->flight_num = flight_num;
  this->num_passengers = num_passengers;
  this->landed = landed;
}


/*
 * Returns wether the plan has landed
*/
bool plane::is_landed() const {
  return this->landed;
}


/* 
 * Lands the plane
 * TODO: Implement fully after the gate class
*/
void plane::land(int *req_vehicles, int &arr_length) {
  this->landed = true;
}


/*
 * Uses Pass by reference to return information regarding the flight
*/
void plane::get_flight_info(std::string &departed_from, int &flight_num, int &num_passengers) const {
  departed_from = this->dep_from;
  flight_num = this->flight_num;
  num_passengers = this->num_passengers;
}

