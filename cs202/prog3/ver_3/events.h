/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * events.h
 *
 * This file holds all edclarations to the event base class and all three events. The event
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

#ifndef __EVENT_H__
#define __EVENT_H__

#include <iostream>
#include <exception>
#include <utility>
#include <list>


/* contains all types of animals for any of the locations */
typedef enum animal_type {
  /* petting zoo */
  goat,
  chicken,
  pig,
  horse,
  /* aquarium */
  penguin,
  seal,
  sea_otter,
  /* safari */
  girrafe,
  leopard,
  lion,

  unknown
} animal_type;



/* Base class for all three events, contains a list of reviews for the given event */
class event {
  public:
    /* constructors + destructors */
    event();
    event(const char *name, int capacity, int length, float ticket_price);
    event(const event &src);

    ~event();

    /* review list functionality */
    bool add_review(std::string &review) throw(std::bad_alloc);
    void display_reviews(std::ostream &output=std::cout) const throw(std::string); // thrown if the list is empty

    /* overloaded operators */
    event &operator=(const event &rhs);
    bool operator==(const event &rhs) const;
    bool operator!=(const event &rhs) const;

    bool operator<(const event &rhs) const;
    bool operator>(const event &rhs) const;
    bool operator<=(const event &rhs) const;
    bool operator>=(const event &rhs) const;
    
    friend std::ostream &operator<<(std::ostream &output, const event &obj);
  private:
    void copy_data(const event &src);

    char *event_name;
    int capacity, length;
    float ticket_price;

    /* this will hold a list of reviews */
    std::list<std::string> reviews;
};



/* represents an event at a petting zoo */
/*
 * Contains a list of animals at a given petting zoo
 */
class petting : public event {
  public:
    /* constructors */
    petting();
    petting(const char *name, int capacity, int length, float ticket_price);

    /* interact with the animal list */
    bool add_animal_type(animal_type t) throw(std::bad_alloc);
    bool does_animal_exist(animal_type t) const;
    void display_all_animals(std::ostream &output=std::cout) const throw(std::string); // thrown if the list is empty

    /* overloaded operators */
    bool operator==(const petting &rhs) const;
    bool operator!=(const petting &rhs) const;

    petting &operator+=(const petting &rhs); /* will append the two animal lists */
    petting &operator+=(const animal_type); /* will append an animal to the animal list */
    petting &operator-=(const petting &rhs); /* will remove all matching entries in the animal list */
    petting &operator-=(const animal_type); /* will remove an animal from the animal list */

    /* friend functions */

    friend petting operator+(const petting &a, animal_type val); /* add an entry to the list */
    friend petting operator+(animal_type val, const petting &p);
    friend petting operator+(const petting &a, const petting &b); /* add two lists together */

    friend petting operator-(const petting &a, animal_type val); /* remove an object from the list */
    friend petting operator-(animal_type val, const petting &p);
    friend petting operator-(const petting &a, const petting &b); /* remove all matching items between the two lists */
    
    friend std::ostream &operator<<(std::ostream &output, const petting &obj);
  private:
    std::list<animal_type> animals;
};



/* contains an aquatic event such as an aquarium */
/*
 * conatians a list of pairs, each pair contains an exhibit at the aquarium
 * as well as what kind of animal is in that exhibit
*/
class aquatic : public event {
  public:
    /* constructors */
    aquatic();
    aquatic(const char *name, int capacity, int length, float ticket_price);

    /* interact with the exhibit list */
    bool add_exhibit(std::string &exhibit_name, animal_type t) throw(std::bad_alloc);
    bool add_exhibit(const std::pair<std::string, animal_type> &) throw(std::bad_alloc);
    void display_exhibits(std::ostream &output=std::cout) const throw(std::string); // thrown if the list is empty
    
    /* overloaded operators */
    bool operator==(const aquatic &rhs) const;
    bool operator!=(const aquatic &rhs) const;

    aquatic &operator+=(const std::pair<std::string, animal_type> &); /* will append a pair to the exhibit list */
    aquatic &operator+=(const aquatic &);
    aquatic &operator-=(const std::pair<std::string, animal_type> &); /* will remove a pair from the exhibit list */
    aquatic &operator-=(const aquatic &);

    /* friend functions */

    friend aquatic operator+(const aquatic &a, const aquatic &b); /* add two aquatic events together, combining their lists */
    friend aquatic operator+(const std::pair<std::string, animal_type> &, const aquatic &b); /* append a pair onto the list */
    friend aquatic operator+(const aquatic &a, const std::pair<std::string, animal_type> &); /* append a pair onto the list */
    
    friend aquatic operator-(const aquatic &a, const aquatic &b); /* remove matching elements in the exhibits list */
    friend aquatic operator-(const std::pair<std::string, animal_type> &, const aquatic &b); /* remove a pair from the list */
    friend aquatic operator-(const aquatic &a, const std::pair<std::string, animal_type> &); /* remove a pair from the list */
    
    friend std::ostream &operator<<(std::ostream &output, const aquatic &obj);
  private:
    /* list of pairs, containing the name of the exhibit, and the animal type associated with that exhibit */
    std::list<std::pair<std::string, animal_type>> exhibits;
};



/* contains a safari event */
/*
 * Contains a list of pairs, each pair contains the name of a region on the safari and a list of what animals
 * can be found in that region.
*/
class safari : public event {
  public:
    /* constructors */
    safari();
    safari(const char *name, std::string &guide, int capacity, int length, float ticket_price); 

    /* interact with the region list */
    bool add_region(std::pair<std::string, std::list<animal_type>> &region) throw(std::bad_alloc);
    bool add_region(std::string &, animal_type *types, size_t length) throw(std::length_error, std::invalid_argument);

    void display_region(std::string &region_name) const throw(std::out_of_range); // thrown if the list is empty
    void display_all_regions() const throw(std::out_of_range); // thrown if the list is empty
    
    /* overloaded operators */
    bool operator==(const safari &rhs) const;
    bool operator!=(const safari &rhs) const;

    safari &operator+=(const std::pair<std::string, std::list<animal_type>> &); /* will append a region onto the list */
    safari &operator+=(const safari &);
    safari &operator-=(const std::pair<std::string, std::list<animal_type>> &); /* will remove a region from the list */
    safari &operator-=(const safari &);

    /* friend functions */

    friend safari operator+(const safari &a, const safari &b); /* add two safari events together, combining their lists */
    friend safari operator+(const safari &a, const std::pair<std::string, std::list<animal_type>> &);
    friend safari operator+(const std::pair<std::string, std::list<animal_type>> &, const safari &a);
    
    friend safari operator-(const safari &a, const safari &b); /* add two safari events together, combining their lists */
    friend safari operator-(const safari &a, const std::pair<std::string, std::list<animal_type>> &);
    friend safari operator-(const std::pair<std::string, std::list<animal_type>> &, const safari &a);
    
    friend std::ostream &operator<<(std::ostream &output, const safari &obj);
  private:
    std::string guide;

    /* list of pairs, containing the name of the region, and the animal types associated with that region */
    std::list<std::pair<std::string, std::list<animal_type>>> regions;
};

#endif
