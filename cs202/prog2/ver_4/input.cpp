/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * input.cpp
 *
 * This file holds a couple helper functions, that are responsible for getting input from the user.
*/

#include "input.h"
#include <iostream>

using namespace std;

/* read in one integer */
void get_input_int(const char *prompt, int &value) {
  cout << prompt;
  cin >> value;
  cin.ignore(100, '\n');
}


/* read in a whole phrase */
void get_input_phrase(const char *prompt, char *value, int length) {
  cout << prompt;
  cin.get(value, length, '\n');
  cin.ignore(100, '\n');
}

