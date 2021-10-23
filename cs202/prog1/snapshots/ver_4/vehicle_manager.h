/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * vehicle_manager.h
 *
 * This file contains all the definitions for both the vehicle manager class and vehicle manager's v_node class
*/

#ifndef __VEHICLE_MANAGER_H__
#define  __VEHICLE_MANAGER_H__

#include <vector>
#include <cstddef>
#include "ground_vehicle.h"

/*
 * represents one node in the vehicle manager's pool (CLL)
*/
class v_node : public ground_vehicle {
  public:
    v_node();
    v_node(const ground_vehicle &data);

    v_node * &get_next();
    void set_next(v_node *);

  private:
    v_node *next;
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
    vehicle_manager(const vehicle_manager &);
    ~vehicle_manager();

    /* functions to interact with the CLL Pool */
    bool add_to_pool(ground_vehicle &veh); // add to the CLL
    bool remove_from_pool(const ground_vehicle &veh); // remove a vehicle from both the busy vector or the CLL
    ground_vehicle *get_vehicle_from_pool(vehicle_type type); // retrieve a vehicle from either the busy vector or the CLL
    bool clear_pool(); // clear out both the busy vector and the CLL

    /* need to request and release vehicles, transfering them from the CLL, and the vector */
    bool request_vehicles(gate *dest_gate, vehicle_type *arr, std::size_t length);
    bool release_vehicles(gate &cur_gate);

  private:
    /* recursively retrieve a vehicle from the class's CLL with matching information */
   ground_vehicle *get_vehicle_from_pool(vehicle_type type, v_node *head);
   v_node *remove_vehicle(v_node * &head, const ground_vehicle &);
   bool clear_list();

    v_node *rear; // free vehicle CLL
    std::vector<ground_vehicle> busy_vehicles; // collection of busy vehicles
};

#endif

