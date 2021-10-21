/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * location.cpp
 *
 * This file contains the declarations for the location class. this class holds and manages a pair
 * of GPS coordinates which are dynamically allocated. This class is the base class for almost
 * all classes in this program.
*/

#ifndef __LOCATION_H__
#define __LOCATION_H__

/*
 * Location class
 * represents a set of gps coordinates and is the base class for almost all of the classes in this program
 *
*/
class location {
  public:
    location(); // default constructor
    location(const location &); // copy constructor
    location(float longitude, float latitude); // normal constructor

    virtual ~location();

    /* Overloaded equality operator, basically becomes the compare function */
    virtual bool operator==(const location &rhs) const;
  protected:
    // get and set the location
    float get_longitude();
    float get_latitude();
    void set_location(float longitude, float latitude);

    // all classes will recieve a input and display function, through dynamic binding
    virtual void input();
    virtual void display();
  private:
    /* dynamically allocated to fit program requirements */
    float *longitude, *latitude;
};

#endif

