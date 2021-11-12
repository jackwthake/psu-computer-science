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
  if (src.event_name) {
    this->event_name = new char[strlen(src.event_name) + 1];
    strcpy(this->event_name, src.event_name);
  } else {
   this->event_name = NULL;
  }

  this->capacity = src.capacity;
  this->length = src.length;
  this->ticket_price = src.ticket_price;
}


event::~event() {
  if (this->event_name)
    delete []this->event_name;
}


bool event::add_review(std::string &review) throw(std::bad_alloc) {
  this->reviews.emplace_front(review);
}


void event::display_reviews(void) throw(std::string) {
  if (this->reviews.empty())
    throw(std::string("Error: Empty Review List"));

  for (std::string rev : this->reviews) {
    std::cout << "Review: " << rev << std::endl;
  }
}

/* overloaded operators */
void event::operator=(const event &rhs) { }
bool event::operator==(const event &rhs) const { }
bool event::operator!=(const event &rhs) const { }

bool event::operator<(const event &rhs) const { }
bool event::operator>(const event &rhs) const { }
bool event::operator<=(const event &rhs) const { }
bool event::operator>=(const event &rhs) const { }

std::ostream &operator<<(std::ostream &output, const event &obj) { }
std::istream &operator>>(std::istream &intput, event &obj) { }
