/*
 * Jack Thake
 * Karla Fant
 * CS 202
 * input.h
 *
 * This file holds a couple helper functions, that are responsible for getting input from the user.
*/

#ifndef __INPUT_H__
#define __INPUT_H__

/* functions to get values from the user in different formats */
void get_input_int(const char *prompt, int &value);
void get_input_phrase(const char *prompt, char *value, int length);

#endif
