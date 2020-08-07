#ifndef PIZZA_LIST_H
#define PIZZA_LIST_H

#include "pizza.h"

struct node {
  pizza data;
  node *next;
};


class pizza_list {
  public:
    pizza_list();
    ~pizza_list();

    void add_pizza();
    void add_pizza(pizza &item);
    pizza *exists(const char *name) const;

    void displ_all() const;
    void displ_most_recent() const;
    void displ_all_with_rating(unsigned rating) const;

  private:
    void bubble_sort();
    void write_to_file() const;

    int length;
    node *head;
};

#endif
