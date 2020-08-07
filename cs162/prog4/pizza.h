/*
 * Jack Thake
 * CS162, Program 3, July 29th, 2020
 *
 * This file holds the declaration of the Pizza struct.
*/

#ifndef PIZZA_H /* include guard */
#define PIZZA_H

const unsigned field_length = 50;
const unsigned price_length = 6;

struct pizza {
  char name[field_length];
  char description[field_length];
  char additions[field_length];
  char removals[field_length];

  int time_added;
  int rating;
  char price[price_length];
};

void read_pizza_from_user(pizza &result);
void print_pizza(pizza &printable);

#endif
