/*
 * Jack Thake, Program 3, Aug 3 2020, CS162
 *
 * This file holds the entry point to the program. This program keeps track of
 * the user entered pizzas and stores them into a data file where the program
 * can also then retrieve all data.
*/

#include "pizza.h"
#include "file.h"
#include "commands.h"

#include <iostream>
using namespace std;

/* max number of pizzas the program can handle */
const int num_pizzas = 20;

/* prototypes */
void main_loop(pizza list[]);


int main(void) {
  pizza list[num_pizzas];

  /* open the data file, do error checking */
  read_file("pizza.txt", list, num_pizzas);

  cout << "Welcome to the pizza noting tool! Created by Jack Thake." << endl;
  helpCommand();

  /* main loop for commands */
  main_loop(list);

  /* close the data file, do error checking */
  if(!write_file("pizza.txt", list, num_pizzas)) {
    cerr << "Failed to write to data file. Exitting." << endl;
    return 0;
  }

  return 1;
}


/* the main driver of the program, loops until the user enters quit, executes commands. */
void main_loop(pizza list[]) {
  bool running = true;

  while(running) {
    int cmd_type = get_user_command(); /* get the entered command type */

    switch(cmd_type) { /* switch the command types (see commands.h) */
      case cmd_create:
        createCommand(list, num_pizzas); /* execute create */
        break;
      case cmd_search:
        searchCommand(list); /* execute search */
        break;
      case cmd_display: /* execute display */
        displayCommand(list);
        break;
      case cmd_help: /* execute help */
        helpCommand();
        break;
      case cmd_quit: /* exit the loop */
        running = !running;
        break;
      default: /* unrecognized command */
        cout << "Unrecognized command." << endl;
        break;
    }
  }
}
