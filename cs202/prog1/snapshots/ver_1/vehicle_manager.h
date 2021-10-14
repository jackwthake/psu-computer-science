/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * vehicle_manager.h
 *
 * This file contains all the definitions for both the vehicle manager class and vehicle manager's node class
*/

#ifndef __VEHICLE_MANAGER_H__
#define  __VEHICLE_MANAGER_H__

#include <vector>
#include "ground_vehicle.h"

/*
 * represents one node in the vehicle manager's pool (CLL)
*/
class node : public ground_vehicle {
  public:
    node();
    node(const ground_vehicle &data);

    node *get_next();
    void set_next(node *);

  private:
    node *next;
};


/* 
 * this class manages all ground vehicles, and interacts with both the ground vehicles
 * anf the airport gates. Available vehiles live in the CLL, once requested the requested
 * vehicles get moved to the busy_vehicle vector and live there until the gate releases them
 * using vehicle_manager's release_vehicles method, which just moves all vehicles in the vector
 * that have the same dest_gate object as is passed to the method.
 */
class vehicle_manager {
  public:
    vehicle_manager();
    ~vehicle_manager();

    /* functions to interact with the CLL Pool */
    bool add_to_pool(ground_vehicle &veh); // add to the CLL
    bool remove_from_pool(const ground_vehicle &veh); // remove a vehicle from both the busy vector or the CLL
    bool clear_pool(); // clear out both the busy vector and the CLL

    /* need to request and release vehicles, transfering them from the CLL, and the vector */
    bool request_vehicles(gate &dest_gate, vehicle_type *arr, size_t length);
    bool release_vehicles(gate &cur_gate);

  private:
    node *rear; // free vehicle CLL
    std::vector<ground_vehicle> busy_vehicles; // collection of busy vehicles
};

#endif


