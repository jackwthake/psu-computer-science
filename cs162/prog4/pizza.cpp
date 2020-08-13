/*
 * Jack Thake, Program 4, Aug 8, 2020
 * CS162
 *
 * This file holds all implementations for the pizza struct's ease of use functions
*/

#include "pizza.h"
#include "input.h"
#include <time.h>

#include <iostream>
using namespace std;

/* read in one pizza prompting the user for each member */
void read_pizza_from_user(pizza &result) {
  /* read in pizza info */
  get_input_phrase("Enter the pizza's name: ", result.name, field_length);
  get_input_phrase("Enter a Description of the pizza: ", result.description, field_length);
  get_input_phrase("Enter any additions to the pizza: ", result.additions, field_length);
  get_input_phrase("Enter any removals from the pizza: ", result.removals, field_length);
  get_input("Enter a Rating from 0 to 5: ", result.rating);
  get_input_word("Enter the price: $", result.price);

  result.time_added = time(NULL);
}


/* print a given pizza's members to the user */
void print_pizza(pizza &printable) {
  cout << endl
       << "----------------------\n"
       << "Name: " << printable.name << "\n"
       << "Description: " << printable.description << "\n"
       << "Additions: " << printable.additions << "\n"
       << "Removals: " << printable.removals << "\n"
       << "Rating (Out of 5): " << printable.rating << "\n" 
       << "Price: $" << printable.price << "\n" 
       << "----------------------\n" << endl;
}

