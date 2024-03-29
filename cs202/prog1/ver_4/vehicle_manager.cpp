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

#include "vehicle_manager.h"
#include <iostream>


/*
 * v_node class implementation
*/


/* 
 * default constructor
*/
v_node::v_node() : ground_vehicle() {
  this->next = NULL;
}


/*
 * normal constructor
*/
v_node::v_node(const ground_vehicle &data) : ground_vehicle(data) {
  this->next = NULL;
}


/*
 * get the next node in the chain
*/
v_node * &v_node::get_next() {
  return this->next;
}


/*
 * set the next node in the chain
*/
void v_node::set_next(v_node *next) {
  this->next = next;
}


/*
 * vehicle_manager class implementation
*/


/*
 * default constructor
*/
vehicle_manager::vehicle_manager() {
  this->rear = nullptr;
}


/*
 * deallocate memory
*/
vehicle_manager::~vehicle_manager() {
  clear_pool();
}


/*
 * add a node to the CLL
*/
bool vehicle_manager::add_to_pool(ground_vehicle &veh) {
  // if the list is empty
  if (!this->rear) {
    this->rear = new v_node(veh);
    this->rear->set_next(this->rear);
    return true;
  } 

  v_node *tmp = this->rear->get_next();
  this->rear->set_next(new v_node(veh));
  this->rear->get_next()->set_next(tmp);

  return true;
}


/*
 * removes a vehicle from wither the busy vector or the CLL
 * depending on the ground vehicle instance
*/
bool vehicle_manager::remove_from_pool(const ground_vehicle &veh) {
  /* if we reach out here then the vehicle should be in the CLL */
  /* check to see if there is just one node in the list */
  if (this->rear == this->rear->get_next()) {
    if (*rear == veh) {
      delete rear;
      rear = nullptr;

      return true;
    }
  }

  /* check if rear is the matching node */
  v_node *prev = this->rear;
  this->rear = this->rear->get_next();
  if (*this->rear == veh) {
    /* grab a temporaroy of the matching node */
    v_node *tmp = this->rear;

    /* unlink the matching node from the list */
    this->rear = this->rear->get_next();
    prev->set_next(this->rear);

    /* deallocate and return */
    delete tmp;
    return true;
  }

  /* otherwise the node is in the middle of the CLL, call the recursive function */
  this->rear = remove_vehicle(this->rear->get_next(), veh);
  return true;
}


/*
 * recursively retrieves a vehicle of a given type from the pool
*/
ground_vehicle *vehicle_manager::get_vehicle_from_pool(vehicle_type type) {
  if (!this->rear) return nullptr;
  if (this->rear->get_type() == type)
    return this->rear;

  return get_vehicle_from_pool(type, this->rear->get_next()); 
}


/*
 * Recursively clear the pool
*/
bool vehicle_manager::clear_pool() {
  if (!this->rear) return false;

  v_node *tmp = this->rear;
  this->rear = this->rear->get_next();
  tmp->set_next(NULL);
  
  return this->clear_list();
}


/*
 * Request vehicles for a given gate
*/
bool vehicle_manager::request_vehicles(gate *dest_gate, vehicle_type *arr, std::size_t length) {
  if (arr) {
    for (int i = 0; i < length; ++i) {
      ground_vehicle *veh = get_vehicle_from_pool(*(arr + i));
      
      if (!veh)
        return false;

      if (!veh->request(dest_gate))
        return false;
    }
  }

  return true;
}


/*
 * Wrapper function to recursively release any vehicles at a given gate
*/
bool vehicle_manager::release_vehicles(gate *cur_gate) {
  if (rear->get_dest_gate() == cur_gate)
    rear->release();

  this->release_vehicles(rear->get_next(), cur_gate);

  return true;
}


void vehicle_manager::display() {
  std::cout << "Vehicles in pool:" << std::endl;
  std::cout << "=========================" << std::endl;
  if (this->rear) {
    this->rear->display();
  
    this->display(this->rear->get_next());
  }
}


/*
 * Recursive functions
*/


/*
 * recursive function to retrieve a vehicle from the CLL
*/
ground_vehicle *vehicle_manager::get_vehicle_from_pool(vehicle_type type, v_node *head) {
  if (!head) return nullptr;
  if (head == this->rear) return nullptr;

  if (head->get_type() == type) {
    return head;
  }

  return this->get_vehicle_from_pool(type, head->get_next());
}


/*
 * Recursively remove a matching object from the middle of a CLL
*/
v_node *vehicle_manager::remove_vehicle(v_node * &head, const ground_vehicle &veh) {
  if (!head || !rear) return nullptr; // no list to check
  if (head == this->rear) return this->rear; // this is the main stopping condition

  /* use tail recursion */
  head->set_next(this->remove_vehicle(head->get_next(), veh));

  /* if we are the matching node */
  if (*head == veh) {
    /* unlink from list */
    v_node *tmp = head;
    head = head->get_next();

    /* deallocate */
    delete tmp;
    return head;
  } 

  return head;
}


/*
 * Recursively releases busy vehicles at a given gate
*/
void vehicle_manager::release_vehicles(v_node *head, const gate *cur_gate) {
  if (!head) return;
  if (head == this->rear) return;

  if (head->get_dest_gate() == cur_gate) {
    head->release();
  }

  this->release_vehicles(head->get_next(), cur_gate);
}


/*
 * clear the CLL
*/
bool vehicle_manager::clear_list() {
  if (!this->rear) return true;

  v_node *tmp = this->rear;
  this->rear = this->rear->get_next();

  delete tmp;
  return this->clear_list();
}


/*
 * recursively print the CLL
*/
void vehicle_manager::display(v_node *head) {
  if (!head) return;
  if (head == this->rear) return;

  head->display();
  std::cout << "=========================" << std::endl;
  this->display(head->get_next());
}
