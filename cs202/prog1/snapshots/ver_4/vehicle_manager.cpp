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


/*
 * removes a vehicle from wither the busy vector or the CLL
 * depending on the ground vehicle instance
*/
bool vehicle_manager::remove_from_pool(const ground_vehicle &veh) {
  /* check if the vehicle is busy */
  if (veh.is_busy()) {
    this->busy_vehicles.erase(std::remove(this->busy_vehicles.begin(), this->busy_vehicles.end(), veh), this->busy_vehicles.end());

    return true;
  }

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
const ground_vehicle *vehicle_manager::get_vehicle_from_pool(vehicle_type type) const {
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
bool vehicle_manager::request_vehicles(gate &dest_gate, vehicle_type *arr, std::size_t length) {
  if (arr) {
    for (int i = 0; i < length; ++i) {
      
    }
  }

  return false;
}


bool vehicle_manager::release_vehicles(gate &cur_gate) {
  return false;
}


/*
 * Recursive functions
*/


/*
 * recursive function to retrieve a vehicle from the CLL
*/
const ground_vehicle *vehicle_manager::get_vehicle_from_pool(vehicle_type type, v_node *head) const {
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
}


bool vehicle_manager::clear_list() {
  if (!this->rear) return true;

  v_node *tmp = this->rear;
  this->rear = this->rear->get_next();

  delete tmp;
  return this->clear_list();
}

