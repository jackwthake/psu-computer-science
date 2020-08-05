/*
 * Jack Thake, Program 3, Aug 3 2020, CS162
 *
 * This file holds all of the prototypes for the user entered commands. 
*/ 

#ifndef COMMANDS_H
#define COMMANDS_H

#include "pizza.h"

/* used to make communication between the functions easier to read */
enum {
  cmd_create = 0,
  cmd_search,
  cmd_display,
  cmd_help,
  cmd_quit,
  cmd_unknown
};

/* length of a normal command */
const int cmd_size = 50;

int get_user_command(void);

/* each of these carries out the functionality of their corresponding function */
void createCommand(pizza list[], int length);
void searchCommand(pizza list[]);
void displayCommand(pizza list[]);
void helpCommand();

#endif

 
