/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * vehicle_manager.cpp
 *
 * This file contains the definition for both the v_node class and the vehicle manager class.
 * The v_node class represents one node in the vehicle manager;s circular linked list of
 * ground vehicles. v_node is derived from ground_vehicle. the ground vehicle class manages
 * a CLL of ground vehicles, that gates can request and release.
*/

#ifndef __VEHICLE_MANAGER_H__
#define  __VEHICLE_MANAGER_H__

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
 * and the airport gates. Available and busy vehicles live in the CLL
*/
class vehicle_manager {
  public:
    vehicle_manager();
    ~vehicle_manager();

    /* functions to interact with the CLL Pool */
    bool add_to_pool(ground_vehicle &veh); // add to the CLL
    bool remove_from_pool(const ground_vehicle &veh); // remove a vehicle from both the busy vector or the CLL
    ground_vehicle *get_vehicle_from_pool(vehicle_type type); // retrieve a vehicle from either the busy vector or the CLL
    bool clear_pool(); // clear out both the busy vector and the CLL

    /* need to request and release vehicles, transfering them from the CLL, and the vector */
    bool request_vehicles(gate *dest_gate, vehicle_type *arr, std::size_t length);
    bool release_vehicles(gate *cur_gate);

    void display();
  private:
    /* recursively retrieve a vehicle from the class's CLL with matching information */
   ground_vehicle *get_vehicle_from_pool(vehicle_type type, v_node *head);
   v_node *remove_vehicle(v_node * &head, const ground_vehicle &);
   void release_vehicles(v_node *head, const gate *);
   bool clear_list();
   void display(v_node *head);

   v_node *rear; // free vehicle CLL
};

#endif

