file.cpp                                                                                            0000600 0040210 0000454 00000004106 13712677430 011311  0                                                                                                    ustar   thake                           them                                                                                                                                                                                                                   /*
 * Jack Thake, Program 3, Aug 3 2020, CS162
 *
 * This file holds all functionality for interecting with a data file.
*/

#include "file.h"

#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;


/* 
 * reads in a portion of the passed file, static because it is not needed in
 * global scope.
*/
static void read_from_file(ifstream &file, char response[], int length) {
  file.get(response, length, '|'); /* read in description member */
  file.ignore(100, '|');
}


/*
 * reads in a data file, filling out the passed array with pizza structs,
 * returns true the file was successfully opened and read from, false otherwise.
*/
void read_file(const char *fp, pizza list[], int length) {
  int index = 0;
  char temp[field_length];

  ifstream data;
  data.open(fp);

  /* dont try to read if the file doesn't exist. */
  if(!data)
    return;

  /* read in until we either reach eof or the end of the array */
  while(!data.eof() && index < length) {
    read_from_file(data, list[index].name, field_length);
    read_from_file(data, list[index].description, field_length);
    read_from_file(data, list[index].additions, field_length);
    read_from_file(data, list[index].removals, field_length);
    read_from_file(data, list[index].price, price_length);

    data >> list[index].rating;
    data.ignore(100, '\n');

    ++index;
  }

  /* cleanup */
  data.close();
} 


/*
 * writes the passed array to the specified data file. returns true if the files
 * was successfully opened and written to, false otherwise.
*/
bool write_file(const char *fp, pizza list[], int length) {
  ofstream data;
  data.open(fp);

  /* don't write if there was an error  */
  if(!data)
    return false;
  
  for(int i = 0; i < length; ++i) {
    if(strcmp(list[i].name, "") != 0) { /* only write in valid structs */
      data << list[i].name << "|"
           << list[i].description << "|"
           << list[i].additions << "|"
           << list[i].removals << "|"
           << list[i].price << "|"
           << list[i].rating << "\n";
    }
  }

  /* cleanup */
  data.close();
  return true;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                          main.cpp                                                                                            0000600 0040210 0000454 00000003564 13712677430 011325  0                                                                                                    ustar   thake                           them                                                                                                                                                                                                                   /*
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
  pizza list[num_pizzas] = { 0 }; /* initialize the array, filling it with 0's */

  /* open the data file, do error checking */
  read_file("pizza.txt", list, num_pizzas);

  cout << "Welcome to the pizza noting tool! Created by Jack Thake." << endl;
  helpCommand();
  
  /* main loop for commands */
  main_loop(list);

  /* close the data file, do error checking */
  if(!write_file("pizza.txt", list, num_pizzas)) {
    cerr << "Failed to write to data file. Exitting." << endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
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

                                                                                                                                            commands.h                                                                                          0000600 0040210 0000454 00000001235 13712677430 011640  0                                                                                                    ustar   thake                           them                                                                                                                                                                                                                   /*
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

 
                                                                                                                                                                                                                                                                                                                                                                   file.h                                                                                              0000600 0040210 0000454 00000000452 13712677430 010756  0                                                                                                    ustar   thake                           them                                                                                                                                                                                                                   /*
 * Jack Thake, Program 3, Aug 3 2020, CS162
 *
 * This file holds all prototypes for interecting with a data file.
*/

#ifndef LIST_H
#define LIST_H

#include "pizza.h"

void read_file(const char *fp, pizza list[], int length);
bool write_file(const char *fp, pizza list[], int length);

#endif
                                                                                                                                                                                                                      pizza.h                                                                                             0000600 0040210 0000454 00000000657 13712677430 011203  0                                                                                                    ustar   thake                           them                                                                                                                                                                                                                   /*
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

  int rating;
  char price[price_length];
};

#endif
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 