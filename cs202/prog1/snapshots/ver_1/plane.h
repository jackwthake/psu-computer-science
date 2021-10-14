/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * plane.h
 *
 * This file contains the definition to the plane class. The plane class inherits from the vehicle
 * class and will be the parent to the node class used in gate's LLL.
*/

#ifndef __PLANE_H__
#define __PLANE_H__

#include <string>
#include "vehicle.h"

/* 
 * Represents one flight either currently landed at the airport, or scheduled to arrive at the airport.
*/
class plane : public vehicle {
  public:
    plane(); // default constructor
    plane(gate &dest_gate, std::string dep_from, int flight_num, int num_passengers, bool landed=false); // normal constructor

    bool is_landed() const; // check if flight is landed

    // the land function will populate an array with the required vehicle types needed to service the plane when it arrives.
    void land(int *req_vehicles, int &arr_length); 
    void get_flight_info(std::string &departed_from, int &flight_num, int &num_passengers) const; // get the flights information
  private:
    std::string dep_from;
    int flight_num, num_passengers;
    bool landed;
};

#endif

