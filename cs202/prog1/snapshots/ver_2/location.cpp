/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * location.cpp
 *
 * This file contains the definitions for the location class. this class holds and manages a pair
 * of GPS coordinates which are dynamically allocated. This class is the base class for almost
 * all classes in this program.
*/

#include "location.h"
#include <iostream>

/*
 * Default constructor, set longitude and latitude to 0
 * We just use the normal constructor.
*/
location::location() : location (0.0f, 0.0f) {
  // not needed
}


/*
 * Copy constructor, just invoke the normal constructor with
 * the dereferenced values from the source object
*/
location::location(const location &src) : location(*src.longitude, *src.latitude) {
  // not needed
}


/*
 * normal constructor - set the longitude and latitude values to the ones passed in
*/
location::location(float longitude, float latitude) {
  this->longitude = new float(longitude);
  this->latitude = new float(latitude);
}


/*
 * deallocate dynamic memory
*/
location::~location() {
  if (this->longitude)
    delete this->longitude;

  if (this->latitude)
    delete this->latitude;
}


/*
 * overloaded equality function
*/
bool location::operator==(const location &rhs) const {
   if (this->longitude && this->latitude) {
     if (rhs.longitude && rhs.longitude) {
       if (*this->longitude == *rhs.longitude) {
         if (*this->latitude == *rhs.latitude) {
           return true;
         }
       }
     }
   }

   return false;
}


/*
 * Input and output functions
*/

/*
 * input values from the user into the location class
*/
void location::input() {
  std::cout << "Please enter the degrees north: ";
  std::cin >> *this->latitude;
  std::cout << "Please enter the degrees east: ";
  std::cin >> *this->longitude;
}


/* 
 * display the contents of the display class to the user
*/
void location::display() {
  if (this->longitude && this->latitude) {
    std::cout << *this->latitude << "\370 N, " << *this->longitude << "\370 E" << std::endl;
  }
}


/*
 * Getters and setters
 * all of these are protected functions
*/

/* 
 * get the longitude if it exists, if not just return NULL
*/
float location::get_longitude() {
  if (this->longitude) // this stops the program from possibly dereferencing a null pointer
    return *this->longitude;

  return 0.0f;
}


/*
 * get the latitude if it exists, if not just return NULL
*/
float location::get_latitude() {
  if (this->latitude) // this stops the program from possibly dereferencing a null pointer
    return *this->latitude;

  return 0.0f;
}


/*
 * set the location, checking if we need to allocate first
*/
void location::set_location(float longitude, float latitude) {
   if (!this->longitude || !this->latitude)
     location(longitude, latitude);

   *this->longitude = longitude;
   *this->latitude = latitude;
}

