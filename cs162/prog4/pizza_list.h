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
    pizza *exists(const char *name);

    void displ_all();
    void displ_most_recent();
    void displ_all_with_rating(unsigned rating);

  private:
    int length;
    node *head;
};

#endif
