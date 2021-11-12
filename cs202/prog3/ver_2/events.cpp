#include "events.h"
#include <cstring>

/**
 * event class implementation
*/
event::event() {
  this->event_name = NULL;
  this->capacity = this->length = 0;
  this->ticket_price = 0.f; 
}


event::event(const char *name, int capacity, int length, float ticket_price) {
  if (name) {
    this->event_name = new char[strlen(name) + 1];
    strcpy(this->event_name, name);
  } else {
    this->event_name = NULL;
  }

  this->capacity = capacity;
  this->length = length;
  this->ticket_price = ticket_price;
}


event::event(const event &src) {
  operator=(src);
}


event::~event() {
  if (this->event_name)
    delete []this->event_name;
}


bool event::add_review(std::string &review) throw(std::bad_alloc) {
  this->reviews.emplace_front(review);

  return true;
}


void event::display_reviews(std::ostream &output) const throw(std::string) {
  if (this->reviews.empty())
    throw(std::string("Error: Empty Review List"));

  for (std::string rev : this->reviews) {
    output << "Review: " << rev << std::endl;
  }
}


/* overloaded operators */
void event::operator=(const event &rhs) {
  if (rhs.event_name) {
    this->event_name = new char[strlen(rhs.event_name) + 1];
    strcpy(this->event_name, rhs.event_name);
  } else {
   this->event_name = NULL;
  }

  this->capacity = rhs.capacity;
  this->length = rhs.length;
  this->ticket_price = rhs.ticket_price;

  this->reviews = std::list<std::string>(rhs.reviews);
}


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


bool event::operator!=(const event &rhs) const {
  if (!operator==(rhs))
    return true;

  return false;
}


bool event::operator<(const event &rhs) const {
  if (strcmp(this->event_name, rhs.event_name) < 0)
    return true;

  return false;
}


bool event::operator>(const event &rhs) const {
  if (strcmp(this->event_name, rhs.event_name) > 0)
    return true;

  return false;
}


bool event::operator<=(const event &rhs) const {
  if (strcmp(this->event_name, rhs.event_name) <= 0)
    return true;

  return false;
}


bool event::operator>=(const event &rhs) const {
  if (strcmp(this->event_name, rhs.event_name) >= 0)
    return true;

  return false;
}


/* friend functions */

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


std::istream &operator>>(std::istream &intput, event &obj) {
  
}
