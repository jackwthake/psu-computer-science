/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * ground_vehicle.cpp
 *
 * This file contains the declarations for the ground_vehicle class. the ground vehicle class
 * manages it's state, wether it's busy or not, as well as it's detsination gate. the ground
 * vehicle class inherits from the vehicle class and is the parent of the v_node class
 */

#ifndef __GROUND_VEHICLE_H__
#define __GROUND_VEHICLE_H__

#include "vehicle.h"

/*
 * Used to identify different ground vehicle types
*/
typedef enum vehicle_type {
  refueler,
  air_starter,
  lavatory,
  unknown
} vehicle_type;


/*
 * Represents one ground vehicle at the airport, responsible for servicing planes.
 * Get's requested by gates when a flight arrives and released when the flight departs.
*/
class ground_vehicle : public vehicle {
  public:
    ground_vehicle(); // default constructor
    ground_vehicle(vehicle_type type, float longitude = 0.0f, float latitude = 0.0f, bool busy=false); // normal constructor

    bool operator==(const ground_vehicle &rhs);

    vehicle_type get_type() const; // get the vehicle's type
    bool request(gate *dest); // request this vehicle, to go to a given gate
    bool release(); // release a vehicle from a given gate 
  private:
    vehicle_type type;
    bool busy;
};

#endif

