#include "pizza.h"
#include "input.h"

#include <iostream>
using namespace std;

void read_pizza_from_user(pizza &result) {
  /* read in pizza info */
  get_input_phrase("Enter the pizza's name: ", result.name, field_length);
  get_input_phrase("Enter a Description of the pizza: ", result.description, field_length);
  get_input_phrase("Enter any additions to the pizza: ", result.additions, field_length);
  get_input_phrase("Enter any removals from the pizza: ", result.removals, field_length);
  get_input("Enter a Rating from 0 to 5: ", result.rating);
  get_input_word("Enter the price: $", result.price);
}

void print_pizza(pizza &printable) {
  cout << endl
       << "----------==----------\n"
       << "Name: " << printable.name << "\n"
       << "Description: " << printable.description << "\n"
       << "Additions: " << printable.additions << "\n"
       << "Removals: " << printable.removals << "\n"
       << "Rating (Out of 5): " << printable.rating << "\n" 
       << "Price: " << printable.price << "\n" 
       << "----------------------\n" << endl;
}

