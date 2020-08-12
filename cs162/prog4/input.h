/*
 * Jack Thake, Program 4, Aug 8, 2020
 * CS162
 *
 * This file holds all prototypes and declarations for the user input functions
*/

#ifndef INPUT_H
#define INPUT_H

/* functions to get values from the user in different formats */
void get_input(const char *prompt, int &value);
void get_input_phrase(const char *prompt, char *value, int length);
void get_input_word(const char *prompt, char *value);

#endif
