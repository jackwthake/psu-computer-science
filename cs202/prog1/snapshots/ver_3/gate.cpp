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
 * copy constructor
*/
gate::gate(const gate &src) {
  // copy over the gate identifier, reallocating if necessary.
  if (this->identifier) {
    delete []this->identifier;
    this->identifier = nullptr;
  }

  if (src.identifier) {
    this->identifier = new char[strlen(src.identifier)];
    strcpy(this->identifier, src.identifier);
  }

  // perform a recursive copy of the lll
  this->head = copy_list(this->head, src.head);
}


/*
 * deallocate memory
*/
gate::~gate() {
  clear_flight_queue();

  if (this->identifier)
    delete []this->identifier;
}


/*
 * add a flight to the queue
*/
bool gate::enqeue_flight(const plane &) {

}


/* 
 * remove a flight from the queue
*/
bool gate::deqeue_flight(int flight_id) {

}


/*
 * clear the flight queue
*/
bool gate::clear_flight_queue() {

}


/*
 * recursive functions
*/


/*
 * recursively copy the queue
*/
p_node *gate::copy_list(p_node *head, p_node *src) {
  if (!src)
    return nullptr;


}


/*
 * recursively get a plane from the queue
*/
const plane &gate::get_flight_info(int flight_id) const {

}

