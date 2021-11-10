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
  sea_otters,
  /* safari */
  girrafe,
  leopard,
  lion
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
    bool add_review(std::string review) throw(std::bad_alloc);
    void display_reviews(void) throw(std::out_of_range); // thrown if the list is empty

    /* getters + setters */
    char *get_name();
    int get_capacity();
    int get_length();
    float get_ticket_price();

    void set_name(const char *);
    void set_capacity(int cap);
    void set_length(int len);
    void set_ticket_price();

    /* overloaded operators */
    void operator=(const event &rhs);
    bool operator==(const event &rhs) const;
    bool operator!=(const event &rhs) const;
    
    friend std::ostream &operator<<(std::ostream &output, const event &obj);
    friend std::istream &operator<<(std::istream &output, const event &obj);
  private:
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
    void display_all_animals() const throw(std::out_of_range); // thrown if the list is empty

    /* overloaded operators */
    void operator=(const petting &rhs);
    bool operator==(const petting &rhs) const;
    bool operator!=(const petting &rhs) const;

    petting &operator+=(const animal_type &); /* will append an animal to the animal list */
    
    friend std::ostream &operator<<(std::ostream &output, const petting &obj);
    friend std::istream &operator<<(std::istream &output, const petting &obj);
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
    bool add_exhibit(std::string exhibit_name, animal_type t) throw(std::bad_alloc);
    std::pair<std::string, animal_type> &get_exhibit(std::string name) const throw(std::out_of_range); // thrown if the list is empty
    void display_exhibits() const throw(std::out_of_range); // thrown if the list is empty
    
    /* overloaded operators */
    void operator=(const aquatic &rhs);
    bool operator==(const aquatic &rhs) const;
    bool operator!=(const aquatic &rhs) const;

    aquatic &operator+=(const std::pair<std::string, animal_type> &); /* will append a pair to the exhibit list */
    
    friend std::ostream &operator<<(std::ostream &output, const aquatic &obj);
    friend std::istream &operator<<(std::istream &output, const aquatic &obj);
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
    safari(const char *name, std::string guide, int capacity, int length, float ticket_price); 

    /* interact with the region list */
    bool add_region(std::pair<std::string, std::list<animal_type>> &region) throw(std::bad_alloc);
    std::pair<std::string, std::list<animal_type>> &construct_region(std::string, int *types, size_t length) throw(std::length_error, std::invalid_argument);

    void display_region(std::string region_name) const throw(std::out_of_range); // thrown if the list is empty
    void display_all_regions() const throw(std::out_of_range); // thrown if the list is empty
    
    /* getters and setters */
    std::string &get_guide() const;
    void set_guide(std::string &);
    
    /* overloaded operators */
    void operator=(const safari &rhs);
    bool operator==(const safari &rhs) const;
    bool operator!=(const safari &rhs) const;

    safari &operator+=(const std::pair<std::string, std::list<animal_type>> &); /* will append a region onto the list */
    
    friend std::ostream &operator<<(std::ostream &output, const safari &obj);
    friend std::istream &operator<<(std::istream &output, const safari &obj);
  private:
    std::string guide;

    /* list of pairs, containing the name of the region, and the animal types associated with that region */
    std::list<std::pair<std::string, std::list<animal_type>>> regions;
};

#endif
