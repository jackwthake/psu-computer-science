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
    void display_all_animals() const;

    void operator=(const petting &rhs);
    bool operator==(const petting &rhs) const;
    bool operator!=(const petting &rhs) const;

    petting &operator+=(const animal_type &);
    
    friend std::ostream &operator<<(std::ostream &output, const petting &obj);
    friend std::istream &operator<<(std::istream &output, const petting &obj);
  private:
    std::list<animal_type> animals;
};



/* contains an aquatic event such as an aquarium */
class aquatic : public event {
  public:
    aquatic();
    aquatic(const char *name, int capacity, int length, float ticket_price);

    /* interact with the exhibit list */
    bool add_exhibit(std::string exhibit_name, animal_type t);
    std::pair<std::string, animal_type> &get_exhibit(std::string name) const;
    void display_exhibits() const;
    
    /* overloaded operators */
    void operator=(const aquatic &rhs);
    bool operator==(const aquatic &rhs) const;
    bool operator!=(const aquatic &rhs) const;

    aquatic &operator+=(const std::pair<std::string, animal_type> &);
    
    friend std::ostream &operator<<(std::ostream &output, const aquatic &obj);
    friend std::istream &operator<<(std::istream &output, const aquatic &obj);
  private:
    /* list of pairs, containing the name of the exhibit, and the animal type associated with that exhibit */
    std::list<std::pair<std::string, animal_type>> exhibits;
};



/* contains a safari event */
class safari : public event {
  public:
    safari();
    safari(const char *name, std::string guide, int capacity, int length, float ticket_price);

    /* interact with the region list */
    bool add_region(std::pair<std::string, std::list<animal_type>> &region);
    std::pair<std::string, std::list<animal_type>> &construct_region(std::string, int *types, size_t length);

    void display_region(std::string region_name) const;
    void display_all_regions() const;
    
    /* getters and setters */
    std::string &get_guide() const;
    void set_guide(std::string &);
    
    /* overloaded operators */
    void operator=(const safari &rhs);
    bool operator==(const safari &rhs) const;
    bool operator!=(const safari &rhs) const;

    safari &operator+=(const std::pair<std::string, std::list<animal_type>> &);
    
    friend std::ostream &operator<<(std::ostream &output, const safari &obj);
    friend std::istream &operator<<(std::istream &output, const safari &obj);
  private:
    std::string guide;

    /* list of pairs, containing the name of the region, and the animal types associated with that region */
    std::list<std::pair<std::string, std::list<animal_type>>> regions;
};

#endif
