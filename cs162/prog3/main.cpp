/*
 * Jack Thake
 * CS162, Program 3, July 29th, 2020
 *
 * This file holds the starting point of the program.
*/


#include <iostream>
using namespace std;

#include "list.h"
#include "pizza.h"
#include "commands.h"

/* prototype */
void introduction(void);



/* entry point */
int main(void) {
  bool running = true;
  list pizzas("pizza.txt"); /* load the list from file. */

  /* welcome the user */
  introduction();

  /* repeat until the user enter's quit */
  while(running) {
    switch(get_user_command()) { /* prompt the user for a command */
      case cmd_type_create:
        create_command(pizzas); /* execute create command */
        break; 
      case cmd_type_search:
        search_command(pizzas); /* execute search command */
        break; 
      case cmd_type_display:
        display_command(pizzas); /* execute display command */
        break; 
      case cmd_type_help:
        help_command(); /* execute help command */
        break; 
      case cmd_type_quit:
        running = false; /* exit the program */
        break; 
      default:
        cout << "Unknown command." << endl; /* not a recognized command */
        break;
    }
  }

  /* exit */
  cout << "Quitting..." << endl;
  pizzas.write_list_to_file("pizza.txt"); /* write changes to file */

  return 0;
}



/*
 * void introduction(void)
 *
 * brief: welcomes the user
*/
void introduction(void) {
  cout << "Welcome to the number 1 Pizza keep-tracker!" << endl;

  /* print all commands */
  help_command();
}
