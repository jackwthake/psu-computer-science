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


/* static helper functions */

/* function to output the animal_id enum type as a string */
static std::ostream &operator<<(std::ostream &output, animal_type &val) {
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
    default:
      output << "Uknown";
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

/* Constructors + Destructors */

/* default */
petting::petting() : event() {
  this->animals = std::list<animal_type>();
}


/* normal */
petting::petting(const char *name, int capacity, int length, float ticket_price) : event(name, capacity, length, ticket_price) {
  this->animals = std::list<animal_type>();
}


/* interact with the animal list */

/* add an animal to the list */
bool petting::add_animal_type(animal_type t) throw(std::bad_alloc) {
  this->animals.emplace_back(t);

  // get rid of duplicates
  this->animals.sort();
  this->animals.unique();

  return true;
}


/* is an animal type present in the animal list */
bool petting::does_animal_exist(animal_type t) const {
  for (animal_type val: this->animals) {
    if (val == t)
      return true;
  }

  return false;
}


/* display a list of all animals present at the event */
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

/* equality operator */
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


/* not equal too */
bool petting::operator!=(const petting &rhs) const {
  if (!this->operator==(rhs))
    return true;

  return false;
}


/* addition assignment operator */

/* add two lists together */
petting &petting::operator+=(const petting &rhs) {
  for (animal_type val : rhs.animals) {
    this->animals.emplace_back(val);
  }

  // remove duplicates
  this->animals.sort();
  this->animals.unique();

  return *this;
}


/* add an animal type onto the list */
petting &petting::operator+=(const animal_type val) {
  this->add_animal_type(val);

  return *this;
}


/* subtraction assignment operator */

/* remove all matching elements */
petting &petting::operator-=(const petting &rhs) {
  for (animal_type targ : rhs.animals) {
    this->animals.remove(targ);  
  }

  return *this;
}


/* look for and remove a specific animal ID */
petting &petting::operator-=(const animal_type val) {
  this->animals.remove(val);

  return *this;
}

/* friend functions */

/* addition operators */

/* add an animal ID to the list */
petting operator+(const petting &p, animal_type val) {
  petting result = p;
  result.add_animal_type(val);

  return result;
}


/* add an animal ID to the list */
petting operator+(animal_type val, const petting &p) {
  petting result = p;
  result.add_animal_type(val);

  return result;
}


/* append a list onto another and then remove duplicates */
petting operator+(const petting &a, const petting &b) {
  petting result = a;
  for (animal_type val_a : a.animals) {
    result.add_animal_type(val_a);
  }

  for (animal_type val_b : b.animals) {
    result.add_animal_type(val_b);
  }

  result.animals.sort();
  result.animals.unique();

  return result;
}


/* subtraction operator */


/* remove an animal ID from the list */
petting operator-(const petting &p, animal_type val) {
  petting result = p;
  result.animals.remove(val);

  return result; 
}


/* remove an animal ID from the list */
petting operator-(animal_type val, const petting &p) {
  petting result = p;
  result.animals.remove(val);

  return result; 
}


/* remove all matching elements from a list returning a copy */
petting operator-(const petting &a, const petting &b) {
  petting result = a;
  for (animal_type val : b.animals) {
    result.animals.remove(val);
  }

  return result;
}


/* insertion operator */
std::ostream &operator<<(std::ostream &output, const petting &obj) {
  operator<<(output, (event)obj);

  output << "\n";
  try {
    obj.display_all_animals();
  } catch (...) {
    output << "No animals currently in the event.";
  }

  return output;
}



/**
 * Aquatic class implementation
*/

/* constructors */

/* default */
aquatic::aquatic() : event() {
  this->exhibits = std::list<std::pair<std::string, animal_type>>();
}


/* normal */
aquatic::aquatic(const char *name, int capacity, int length, float ticket_price) : event(name, capacity, length, ticket_price) {
  this->exhibits = std::list<std::pair<std::string, animal_type>>();
}


/* interact with the exhibit list */

/* add an exhibit to the list and have the aquatic class construct the pair */
bool aquatic::add_exhibit(std::string &exhibit_name, animal_type t) throw(std::bad_alloc) {
  this->exhibits.emplace_back(make_pair(exhibit_name, t));  

  return true;
}


/* add an exhibit to the list with a pre-made pair */
bool aquatic::add_exhibit(const std::pair<std::string, animal_type> &obj) throw(std::bad_alloc) {
  this->exhibits.emplace_back(obj);

  return true;
}


/* display all exhibits */
void aquatic::display_exhibits(std::ostream &output) const throw(std::string) {
  if (this->exhibits.empty())
    throw(std::string("Error: empty list"));

  output << "Exhibit List:\n";
  for (auto val : this->exhibits) {
    output << val.first << " exhibit has " << val.second << "s\n"; 
  }
}

/* overloaded operators */

/* equality operator */
bool aquatic::operator==(const aquatic &rhs) const {
  if (this == &rhs)
    return true;

  if (event::operator==(rhs)) {
    if (this->exhibits == rhs.exhibits) {
      return true;
    }
  }

  return false;
}


/* inequality */
bool aquatic::operator!=(const aquatic &rhs) const {
  if (!this->operator==(rhs))
    return true;

  return false;
}


/* addition assignmnet operator, append a pair onto the list */
aquatic &aquatic::operator+=(const std::pair<std::string, animal_type> &to_add) {
  this->add_exhibit(to_add);

  return *this;
}


/* append another list onto the list */
aquatic &aquatic::operator+=(const aquatic &obj) {
  for (auto &pair : obj.exhibits) {
    this->add_exhibit(pair);
  }

  return *this;
}


/* remove an exhibit from the list */
aquatic &aquatic::operator-=(const std::pair<std::string, animal_type> &obj) {
  this->exhibits.remove(obj);

  return *this;
}


/* remove all matching elements */
aquatic &aquatic::operator-=(const aquatic &obj) {
  for (auto &pair : obj.exhibits) {
    this->exhibits.remove(pair);
  }   

  return *this;
}


/* friend functions */


/* addition operators */

/* add two lists together */
aquatic operator+(const aquatic &a, const aquatic &b) {
  aquatic res = a;

  for (auto &pair : b.exhibits) {
    res.exhibits.emplace_back(pair);
  }

  res.exhibits.sort();
  res.exhibits.unique();

  return res;
}


/* append a pair onto the list */
aquatic operator+(const std::pair<std::string, animal_type> &a, const aquatic &b) {
  aquatic res = b;
  res.add_exhibit(a);

  return res;
}


/* append a pair onto the list */
aquatic operator+(const aquatic &a, const std::pair<std::string, animal_type> &b) {
  aquatic res = a;
  res.add_exhibit(b);

  return res;
}


/* subtraction operators */

/* remove all matching elements */
aquatic operator-(const aquatic &a, const aquatic &b) {
  aquatic res = a;
  for (auto &pair : b.exhibits) {
    res.exhibits.remove(pair);
  }

  return res;
}


/* remove a given pair from the list */
aquatic operator-(const std::pair<std::string, animal_type> &a, const aquatic &b) {
  aquatic res = b;
  res.exhibits.remove(a);

  return res;
}


/* remove a given pair from the list */
aquatic operator-(const aquatic &a, const std::pair<std::string, animal_type> &b) {
  aquatic res = a;
  res.exhibits.remove(b);

  return res;
}


/* insertion operator */
std::ostream &operator<<(std::ostream &output, const aquatic &obj) {
  operator<<(output, (event)obj);

  output << "\n";
  try {
    obj.display_exhibits(output);
  } catch (...) {
    output << "No exhibits to display";
  }

  return output;
}



/**
 * Safari class implementation
*/


/* constructors + destructors */

/* default */
safari::safari() : event() {
  this->regions = std::list<std::pair<std::string, std::list<animal_type>>>();
  this->guide = "";
}


/* normal */
safari::safari(const char *name, std::string &guide, int capacity, int length, float ticket_price) : event(name, capacity, length, ticket_price) {
  this->regions = std::list<std::pair<std::string, std::list<animal_type>>>();
  this->guide = guide;
} 


/* interact with the region list */

/* add a region to the list from an already constructed pair */
bool safari::add_region(const std::pair<std::string, std::list<animal_type>> &region) throw(std::bad_alloc) {
  this->regions.emplace_back(region);

  return true;
}


/* add a region to the list from an array of animal IDs */
bool safari::add_region(std::string &region, animal_type *types, size_t length) throw(std::length_error, std::invalid_argument) {
  if (!types) {
    throw(std::invalid_argument("Error: Animal ID array invalid."));
  } else if (length <= 0) {
    throw(std::length_error("Error: Animal ID array with invalid length (less than or equal to 0)."));
  }

  /* construct the list */
  std::list<animal_type> ids;
  for (int i = 0; i < length; ++i) {
    ids.emplace_front(types[i]);
  }

  /* make the pair and then add it to the regions list */
  std::pair<std::string, std::list<animal_type>> pair = make_pair(region, ids);
  this->regions.emplace_front(pair);

  return true;
}


/* display a given region based on name */
void safari::display_region(std::string &region_name) const throw(std::out_of_range) {
  if (this->regions.empty()) {
    throw(std::out_of_range("Error: Empty region list."));
  }

  for (auto &pair: this->regions) {
    if (pair.first == region_name) { /* if found, print out it's details */
      std::cout << "Region " << pair.first << " contains the following animals:" << std::endl;
      std::cout << "=====================" << std::endl;

      for (animal_type id : pair.second) {
        std::cout << id << std::endl; 
      }

      /* we return because we no longer need to iterate through the list */
      return;
    }
  }
}


/* display all regions to a given ostream */
void safari::display_all_regions(std::ostream &output) const throw(std::out_of_range) {
  if (this->regions.empty()) {
    throw(std::out_of_range("Error: Empty region list."));
  }

  for (auto &pair : this->regions) {
    output << "Region " << pair.first << " contains the following animals:" << std::endl;
    output << "=====================" << std::endl;

    for (animal_type id : pair.second) {
      output << id << std::endl; 
    }
  }
}


/* Overloaded operators */

/* equality operator */
bool safari::operator==(const safari &rhs) const {
  if(event::operator==(rhs)) {
    if (this->guide == rhs.guide && this->regions == rhs.regions) {
      return true;
    }
  }

  return false;
}


/* inequality operator */
bool safari::operator!=(const safari &rhs) const {
  if (!safari::operator==(rhs)) {
    return true;
  }

  return false;
}


/* addition assignment operators */

/* add a region onto a list */
safari &safari::operator+=(const std::pair<std::string, std::list<animal_type>> &region) {
  this->add_region(region);

  return *this;
}


/* combine two lists */
safari &safari::operator+=(const safari &rhs) {
  for (const std::pair<std::string, std::list<animal_type>> &pair : rhs.regions) {
    this->add_region(pair);
  }

  return *this;
}



/* subtraction assignment operators */

/* remove a region */
safari &safari::operator-=(const std::pair<std::string, std::list<animal_type>> &region) {
  this->regions.remove(region);

  return *this;
}


/* remove all matching elements from another region list */
safari &safari::operator-=(const safari &rhs) {
  for (auto &pair : rhs.regions) {
    this->regions.remove(pair);
  }

  return *this;
}


/* friend functions */

/* addition oeprators */

/* add two lists together */
safari operator+(const safari &a, const safari &b) {
  safari result = a;
  result += b;

  return result;
}


/* add a region onto a list */
safari operator+(const safari &a, const std::pair<std::string, std::list<animal_type>> &pair) {
  safari result = a;
  result += pair;

  return result;
}


/* add a region onto a list */
safari operator+(const std::pair<std::string, std::list<animal_type>> &pair, const safari &a) {
  safari result = a;
  result += pair;

  return result;
}


/* subtraction operators */

/* remove all matching elements from one region list */
safari operator-(const safari &a, const safari &b) {
  safari result = a;
  result -= b;

  return result;
}


/* remove a region from the list */
safari operator-(const safari &a, const std::pair<std::string, std::list<animal_type>> &pair) {
  safari result = a;
  result -= pair;

  return result;
}


/* remove a region from the list */
safari operator-(const std::pair<std::string, std::list<animal_type>> &pair, const safari &a) {
  safari result = a;
  result -= pair;

  return result;
}


/* insertion operator */
std::ostream &operator<<(std::ostream &output, const safari &obj) {
  operator<<(output, (event)obj);
  
  output << "\nThis safari has the following regions: \n";

  try {
    obj.display_all_regions(output);
  } catch (...) {
    output << "No regions have been added to this safari, yet.";
  }

  return output;
}

