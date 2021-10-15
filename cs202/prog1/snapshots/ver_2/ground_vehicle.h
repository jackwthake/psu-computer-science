/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * ground_vehicle.h
 *
 * This file contains the definition for both the vehicle type enum and the ground vehicle
 * class, the ground vehicle class inherits from the vehicle class and has no children.
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
  lavatory
} vehicle_type;


/*
 * Represents one ground vehicle at the airport, responsible for servicing planes.
 * Get's requested by gates when a flight arrives and released when the flight departs.
*/
class ground_vehicle : public vehicle {
  public:
    ground_vehicle(); // default constructor
    ground_vehicle(vehicle_type type, bool busy=false); // normal constructor

    vehicle_type get_type() const; // get the vehicle's type
    bool request(gate &dest); // request this vehicle, to go to a given gate
    bool release(); // release a vehicle from a given gate 
  private:
    vehicle_type type;
    bool busy;
};

#endif

