#ifndef __EVENT_H__
#define __EVENT_H__

#include <iostream>
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



/* ABT for all three events, a list of reviews for the given event */
class event {
  public:
    /* constructors + destructors */
    event();
    event(const char *name, int capacity, int length, float ticket_price);
    event(const event &src);

    ~event();

    /* review list functionality */
    bool add_review(std::string review);
    void display_reviews(void);

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
    virtual void operator=(const event &rhs);
    virtual bool operator==(const event &rhs) const;
    virtual bool operator!=(const event &rhs) const;
    
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
class petting : public event {
  public:
    petting();
    petting(const char *name, int capacity, int length, float ticket_price);

    bool add_animal_type(animal_type t);
    void display_all_animals();

    void operator=(const petting &rhs);
    bool operator==(const petting &rhs) const;
    bool operator!=(const petting &rhs) const;

    // TODO: find wether += is an rvalue or lvalue operation
    
    friend std::ostream &operator<<(std::ostream &output, const petting &obj);
    friend std::istream &operator<<(std::istream &output, const petting &obj);
  private:
    std::list<int> animals;
};



/* contains an aquatic event such as an aquarium */
class aquatic : public event {
  public:
    aquatic();
    aquatic(const char *name, int capacity, int length, float ticket_price);

    /* interact with the exhibit list */
    bool add_exhibit(std::string exhibit_name, animal_type t);
    std::pair<std::string, animal_type> &get_exhibit(std::string name);
    void display_exhibits();
    
    /* overloaded operators */
    void operator=(const aquatic &rhs);
    bool operator==(const aquatic &rhs) const;
    bool operator!=(const aquatic &rhs) const;

    // TODO: find wether += is an rvalue or lvalue operation
    
    friend std::ostream &operator<<(std::ostream &output, const aquatic &obj);
    friend std::istream &operator<<(std::istream &output, const aquatic &obj);
  private:
    /* list of pairs, containing the name of the exhibit, and the animal type associated with that exhibit */
    std::list<std::pair<std::string, animal_type>> exhibits;
};


/* contains a safari event */
class safari : public event {
  
};

#endif
