#ifndef __EVENT_H__
#define __EVENT_H__

#include <iostream>
#include <list>


/* contains all types of animals for any of the locations */
enum animal_types {
  goat,
  chicken,
  pig,
  horse
};



/* ABT for all three events, a list of reviews for the given event */
class event {
  public:
    /* constructors + destructors */
    event();
    event(const char *name, int capacity, int length);
    event(const event &src);

    ~event();

    /* review list functionality */
    bool add_review(std::string review);
    void display_reviews(void);

    /* getters + setters */
    char *get_name();
    int get_capacity();
    int get_length();

    void set_name(const char *);
    void set_capacity(int cap);
    void set_length(int len);


    /* overloaded operators */
    virtual void operator=(const event &rhs);
    virtual bool operator==(const event &rhs);
    virtual bool operator!=(const event &rhs);
    
    friend std::ostream &operator<<(std::ostream &output, const event &obj);
    friend std::istream &operator<<(std::istream &output, const event &obj);
  private:
    char *event_name;
    int capacity, length;

    /* this will hold a list of reviews */
    std::list<std::string> reviews;
};



/* represents an event at a petting zoo */
class petting : public event {
  public:
    petting();
    petting(const char *name, int capacity, int length);
  private:
    int *animals;
};

#endif
