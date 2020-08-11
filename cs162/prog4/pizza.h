/*
 * Jack Thake
 * CS162, Program 3, July 29th, 2020
 *
 * This file holds the declaration of the Pizza struct.
*/

#ifndef PIZZA_H /* include guard */
#define PIZZA_H

const unsigned field_length = 50; /* length of most members in pizza struct */
const unsigned price_length = 6; /* amount of characters in a price */

/* represents one pizza in the program */
struct pizza {
  char name[field_length];
  char description[field_length];
  char additions[field_length];
  char removals[field_length];

  int time_added;
  int rating;
  char price[price_length];
};

/* functions to both input and output one pizza struct */
void read_pizza_from_user(pizza &result);
void print_pizza(pizza &printable);

#endif
