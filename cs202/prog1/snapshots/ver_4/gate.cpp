/*
 * Jack Thake
 * Karla Fanta
 * CS202
 * gate.cpp
 *
 * This file holds the implementation for both the gate class, and the p_node class.
 * THe gate class manages a queue of the future arriving flights, while the p_node class
 * represents one node in the queue's LLL. gate is a child of location, p_node is a child
 * of the plane class.
*/


#include "gate.h"
#include <cstring>

/*
 * Node class implementation
*/

/*
 * default constructor
*/
p_node::p_node() : plane() {
  this->next = NULL;
}


/*
 * normal constructor
*/
p_node::p_node(const plane &data) : plane(data) {
  this->next = NULL;
}


/* 
 * copy constructor
*/
p_node::p_node(const p_node &src) : plane(src) {
  this->next = nullptr;
}


/*
 * get the next node in the list
*/
p_node *p_node::get_next() {
  return this->next;
}


/*
 * set the next node in the list
*/
void p_node::set_next(p_node *new_next) {
  this->next = new_next;
}


/*
 * Gate class implementation
*/


/*
 * default constructor
*/
gate::gate() : location(0.f, 0.f) {
  this->identifier = NULL;
  this->head = nullptr;
}


/*
 * normal constructor
*/
gate::gate(char *identifier, float longitude, float latitude) : location(longitude, latitude) {
  if (identifier) {
    this->identifier = new char[strlen(identifier)];
    strcpy(this->identifier, identifier);   
  } else {
    this->identifier = nullptr;
  }

  this->head = nullptr;
}


/*
 * deallocate memory
*/
gate::~gate() {
  // clear queue
  clear_flight_queue();

  // deallocate identifier
  if (this->identifier)
    delete []this->identifier;
}


/*
 * add a flight to the queue
*/
bool gate::enqueue_flight(const plane &src) {
  if (!this->head) { // if the list is empty, just set head to a new node
    this->head = new p_node(src);

    return true;
  } else { // otherwise recursively traverse to the end of the list
    /* recursively append onto end of LLL */
    return append_flight(this->head, src);
  }

  return false;
}


/* 
 * this functions acts as a deqeue or removal function for the LLL,
 * once a plane is removed, itll wait until the flight is ready to depart
 * and then destroy the plane object.
*/
bool gate::land_flight() {
  if (!this->head)
    return false;

  p_node *tmp = this->head;
  this->head = this->head->get_next();

  tmp->land();

  // TODO: read in numer of vehicles needed
  // TODO: wait for plane to leave
  
  delete tmp;
  return true;
}


/*
 * clear the flight queue
*/
bool gate::clear_flight_queue() {
  return clear_list();
}


/*
 * return the first flight with a matching flight number
*/
const plane gate::get_flight_info(int flight_id) const {
  const plane *res = this->get_flight_info(this->head, flight_id);

  if (!res)
    return plane();

  return *res;
};


/*
 * recursive functions
*/


/*
 * recursively append a flight onto the queue
*/
bool gate::append_flight(p_node *head, const plane &src) {
  if (!head) return false; // base case
  if (!head->get_next()) { // last list node
    head->set_next(new p_node(src)); // append a new node

    return true; 
  }

  return append_flight(head->get_next(), src);
}


/*
 * Recursively clear the list
*/
bool gate::clear_list() {
  if (!this->head) return true; // base case

  // grab a temporary
  p_node *tmp = this->head;
  // advance the head pointer
  this->head = this->head->get_next();

  // delete the old head
  delete tmp;

  return this->clear_list();
}


const plane *gate::get_flight_info(p_node *head, int flight_id) const {
  if (!head) return nullptr;

  std::string dep;
  int flight_num, passengers;

  head->get_flight_info(dep, flight_num, passengers);
  if (flight_num == flight_id) {
    return head;
  }

  return get_flight_info(head->get_next(), flight_id);
}
