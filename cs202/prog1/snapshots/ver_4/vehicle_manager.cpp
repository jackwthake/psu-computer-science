#include "vehicle_manager.h"

#include <algorithm>


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
v_node *v_node::get_next() {
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
  this->busy_vehicles = std::vector<ground_vehicle>();  
}


/*
 * copy constyructor
*/
vehicle_manager::vehicle_manager(const vehicle_manager &) {
  // TODO: implement me
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


bool vehicle_manager::remove_from_pool(const ground_vehicle &veh) {
  if (veh.is_busy()) {
    this->busy_vehicles.erase(std::remove(this->busy_vehicles.begin(), this->busy_vehicles.end(), veh), this->busy_vehicles.end());

    return true;
  }

//  return 
//  TODO: implement recursive remove function
}


const ground_vehicle &vehicle_manager::get_vehicle_from_pool(const ground_vehicle &veh) const { }
bool vehicle_manager::clear_pool() {
  if (!this->rear) return false;

  v_node *tmp = this->rear;
  this->rear = this->rear->get_next();
  tmp->set_next(NULL);
  
  return this->clear_list();
}

bool vehicle_manager::request_vehicles(gate &dest_gate, vehicle_type *arr, std::size_t length) { }
bool vehicle_manager::release_vehicles(gate &cur_gate) { }


/*
 * Recursive functions
*/


bool vehicle_manager::remove_vehicle(v_node *rear, v_node *prev, v_node *current, const ground_vehicle &veh) {
  if (!rear || current == rear) return false;

  if (*current == veh) {
    v_node *tmp = current;
    prev->set_next(current->get_next()); 

    // TODO implement me
  }
}


bool vehicle_manager::clear_list() {
  if (!this->rear) return true;

  v_node *tmp = this->rear;
  this->rear = this->rear->get_next();

  delete tmp;
  return this->clear_list();
}
