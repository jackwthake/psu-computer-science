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
  copy_list(this->head, src.head);
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
 * remove a flight from the queue
*/
bool gate::deqeue_flight(int flight_id) {
  return false;
}


/*
 * clear the flight queue
*/
bool gate::clear_flight_queue() {
  return clear_list();
}


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


/*
 * Recursively copy one LLL to another
*/
bool gate::copy_list(p_node *dest, p_node *src) {
  return false;
}

