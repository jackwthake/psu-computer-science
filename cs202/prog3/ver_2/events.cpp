/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * events.cpp
 *
 * This file holds all implementations to the event base class and all three events. The event
 * base class contains basic information regarding an event along with a list of reviews for 
 * that given event. The petting class inherits from the event class and represents an event
 * at a petting zoo and holds a list of all animals at said petting zoo. The aquatic class
 * inherits from the event class and represents an aquarium and all it's various exhibits with 
 * animals, it contains a list of pairs where each pair contains the exhibit name, as well as 
 * the animal ID of the animal present in that exhibit. The safari class inherits from the
 * event class and represents a guided tour through a safari. It contains a list of pairs
 * representing each region of the safari, each pair contains the region name and a list
 * of all animal IDs present in that region.
*/

#include "events.h"
#include <cstring>


std::ostream &operator<<(std::ostream &output, animal_type &val) {
  switch (val) {
    case animal_type::goat:
      output << "Goat";
      break;
    case animal_type::chicken:
      output << "Chicken";
      break;
    case animal_type::pig:
      output << "Pig";
      break;
    case animal_type::horse:
      output << "Horse";
      break;
    case animal_type::penguin:
      output << "Penguin";
      break;
    case animal_type::seal:
      output << "Seal";
      break;
    case animal_type::sea_otter:
      output << "Sea Otter";
      break;
    case animal_type::girrafe:
      output << "Girrafe";
      break;
    case animal_type::leopard:
      output << "Leopard";
      break;
    case animal_type::lion:
      output << "Lion";
      break;
  }

  return output;
}


/**
 * event class implementation
*/

/* Constructors + Destructor */

/* default */
event::event() {
  this->event_name = NULL;
  this->capacity = this->length = 0;
  this->ticket_price = 0.f; 
}


/* normal */
event::event(const char *name, int capacity, int length, float ticket_price) {
  if (name) {
    this->event_name = new char[strlen(name) + 1];
    this->event_name = strcpy(this->event_name, name);
  } else {
    this->event_name = NULL;
  }

  this->capacity = capacity;
  this->length = length;
  this->ticket_price = ticket_price;
}


/* copy */
event::event(const event &src) {
  this->copy_data(src);
}


/* deallocate */
event::~event() {
  if (this->event_name)
    delete []this->event_name;

  this->event_name = NULL;
}


/* interact with review list */

/* adds a review to the list */
bool event::add_review(std::string &review) throw(std::bad_alloc) {
  this->reviews.emplace_front(review);

  return true;
}


/* display all reviews, throwin an exception if the list is empty */
void event::display_reviews(std::ostream &output) const throw(std::string) {
  if (this->reviews.empty())
    throw(std::string("Error: Empty Review List"));

  for (std::string rev : this->reviews) {
    output << "Review: " << rev << std::endl;
  }
}


/* overloaded operators */

/* assignment operator */
event &event::operator=(const event &rhs) {
  if (this == &rhs) // check self assignment
    return *this;
  if (this->event_name) // deallocate passed memory;
    delete []this->event_name;

  this->copy_data(rhs);

  return *this;
}


/* equality operator */
bool event::operator==(const event &rhs) const {
  if (strcmp(this->event_name, rhs.event_name) == 0) {
    if (this->capacity == rhs.capacity && this->length == rhs.length) {
      if (this->ticket_price == rhs.ticket_price) {
        if (this->reviews == rhs.reviews) {
          return true;
        }
      }
    }
  }

  return false;
}


/* not equal operator */
bool event::operator!=(const event &rhs) const {
  if (!operator==(rhs))
    return true;

  return false;
}


/* less than operator */
bool event::operator<(const event &rhs) const {
  if (strcmp(this->event_name, rhs.event_name) < 0)
    return true;

  return false;
}


/* greator than operator */
bool event::operator>(const event &rhs) const {
  if (strcmp(this->event_name, rhs.event_name) > 0)
    return true;

  return false;
}


/* less than or equal to */
bool event::operator<=(const event &rhs) const {
  if (strcmp(this->event_name, rhs.event_name) <= 0)
    return true;

  return false;
}


/* greator than or equal to */
bool event::operator>=(const event &rhs) const {
  if (strcmp(this->event_name, rhs.event_name) >= 0)
    return true;

  return false;
}


/* friend functions */

/* output to an ostream */
std::ostream &operator<<(std::ostream &output, const event &obj) {
  output << "Event with name " << obj.event_name << " has a maximum capacity of " << obj.capacity << ". \n" \
         << obj.event_name << " lasts " << obj.length << " minutes and has a ticket price of $" << obj.ticket_price << ". \n" \
         << "This event has the following reviews: \n";
  
  try {
    obj.display_reviews(output);
  } catch (...) {
    output << "No reviews entered yet.";
  }

  return output;
}


/* private member functions */

/* copy data into the object */
void event::copy_data(const event &src) {
  if (src.event_name) {
    this->event_name = new char[strlen(src.event_name) + 1];
    this->event_name = strcpy(this->event_name, src.event_name);
  } else {
    this->event_name = NULL;
  }

  this->capacity = src.capacity;
  this->length = src.length;
  this->ticket_price = src.ticket_price;
}



/**
 * petting class implementation
*/
petting::petting() : event() {
  this->animals = std::list<animal_type>();
}


petting::petting(const char *name, int capacity, int length, float ticket_price) : event(name, capacity, length, ticket_price) {
  this->animals = std::list<animal_type>();
}


/* interact with the animal list */

bool petting::add_animal_type(animal_type t) throw(std::bad_alloc) {
  this->animals.emplace_back(t);

  // get rid of duplicates
  this->animals.sort();
  this->animals.unique();

  return true;
}


bool petting::does_animal_exist(animal_type t) const {
  for (animal_type val: this->animals) {
    if (val == t)
      return true;
  }

  return false;
}


void petting::display_all_animals(std::ostream &output) const throw(std::string) {
  unsigned i = 0;

  if (this->animals.empty())
    throw(std::string("Error: Empty list."));

  output << "Animals available at event:\n";
  for (animal_type val: this->animals) {
    output << ++i << " | " << val << std::endl;
  }
}


/* overloaded operators */
bool petting::operator==(const petting &rhs) const {
  if (this == &rhs)
    return true;

  if (event::operator==(rhs)) {
    if (this->animals == rhs.animals) {
      return true;
    }
  }

  return false;
}


bool petting::operator!=(const petting &rhs) const {
  if (!this->operator==(rhs))
    return true;

  return false;
}


petting &petting::operator+=(const animal_type &) { }
petting &petting::operator-=(const animal_type &) { }

/* friend functions */

petting operator+(const petting &a, const petting &b) { }
petting operator-(const petting &a, const petting &b) { }

std::ostream &operator<<(std::ostream &output, const petting &obj) {
  operator<<(output, (event)obj);

  try {
    obj.display_all_animals();
  } catch (...) {
    output << "No animals currently in the event.";
  }

  return output;
}

