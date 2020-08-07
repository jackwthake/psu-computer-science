/*
 * Jack Thake, Program 3, Aug 3 2020, CS162
 *
 * This file holds all functionality regarding the user entered commands.
*/

#include "commands.h"
#include <iostream>
using namespace std;


/* 
 * this function reads in one singular integer, static because we don't need it
 * outside this translation unit.
*/
static void get_input(const char *prompt, int &value) {
  cout << prompt; /* print prompt to user */
  
  /* read in value */
  cin >> value;

  /* flush input buffer */
  cin.ignore(100, '\n');  
}


/* 
 * this function reads in a single string of text, static because we don't need it
 * outside this translation unit.
*/
static void get_input(const char *prompt, char *res, int len) {
  cout << prompt; /* print prompt to user  */

  /* respect array bounds while recieving input */
  cin.width(len);
  cin.get(res, len, '\n');

  /* flush input buffer */
  cin.ignore(100, '\n');
}


/* 
 * this function takes in a string from the user, and removes all spaces, sets
 * everything to lowercase as well - makes parsing easier
 */
static void refine_command(char *cmd, char *refined) {
  int j = 0; /* holds the current position in the refined string */

  /* loop through the passed command */
  for(int i = 0; i < strlen(cmd); ++i) {
    if(!isspace(cmd[i])) { /* only fires if the current char is not a space */
      refined[j] = tolower(cmd[i]); /* move over that specific character */
      ++j; /* we only increment j when we've set a char in the refined pointer */
    }
  }

  /* set null terminator */
  refined[j] = '\0';
}


/* 
 * prompts the user for a command, parses the input, returns an integer value
 * representing the command that was entered (see the commands.h) 
*/
int get_user_command(void) {
  char buf[cmd_size]; /* buffer for the un-refined command to be stored in */
  char cmd[cmd_size]; /* array for the refined command to be stored in */
  get_input("Please enter a command: ", buf, cmd_size); /* prompt the user, recieve input into the buffer */

  /* refine the command, remove spaces, and convert the command to lowercase */
  refine_command(buf, cmd);

  /* test which command was entered, returning the corresponding enum value */
  if(strcmp(cmd, "create") == 0) 
    return cmd_create; /* create command */
  if(strcmp(cmd, "search") == 0)
    return cmd_search; /* search command */
  if(strcmp(cmd, "display") == 0)
    return cmd_display; /* display command */
  if(strcmp(cmd, "help") == 0)
    return cmd_help; /* help command */
  if(strcmp(cmd, "quit") == 0)
    return cmd_quit; /* quit command */
  else
    return cmd_unknown; /* unknown command */
}


/* adds one struct to the array so long as the available space permits */
void createCommand(pizza list[], int length) {
  int index = 0; /* holds position in the array */

  /* loop until we find an empty array index */
  while(strcmp(list[index].name, "") != 0) 
    ++index;

  /* check if that index is within bounds */
  if(index < length) {
    /* recieve from the user the various members of the pizza */
    get_input("Please enter the pizza's name: ", list[index].name, field_length);
    get_input("Please enter the pizza's description: ", list[index].description, field_length);
    get_input("Please enter the pizza's additions: ", list[index].additions, field_length);
    get_input("Please enter the pizza's removals: ", list[index].removals, field_length);
    get_input("Please enter the pizza's price: $", list[index].price, price_length);
    get_input("Please enter the pizza's rating out of 5: ", list[index].rating);
  } else {
    /* no more space */
    cout << "Max number of pizzas have already been created." << endl;
  }
}


/*
 * searches the passed array for a user entered name, if it exists, print its
 * info otherwise state nothing was found.
*/
void searchCommand(pizza list[]) {
  int index = 0; /* position in array */
  char tester[field_length]; /* holds the name to search for */

  /* get the name from the user to search for */
  get_input("Please enter the search name: ", tester, field_length);

  /*
   * NOTE: this could've very easily have been done with a for loop, we just
   * only want to loop through used ones which will have a filled out name, as I
   * zero initialize the array
  */
  while(strcmp(list[index].name, "") != 0) {
    if(strcmp(list[index].name, tester) == 0) { /* if the name exists, print it */
      cout << "----------------------" << endl;
      cout << list[index].name << "\t$" << list[index].price << '\n'
           << list[index].description << '\n'
           << "Rating: " << list[index].rating << " out of 5\n"
           << "----------------------" << endl;

      /* we don't need to keep looping if we've already found what we're looking for */
      return;
    }

    /* increment our position */
    ++index;
  }

  /* if we reach out here then nothing was found */
  cout << "No result found with that name." << endl;
}


/* prints all pizzas in the array */
void displayCommand(pizza list[]) {
  int index = 0; /* position in array */
  
  /* formatting */
  cout << "----------------------" << endl;

  /* only loop through used pizzas */
  while(strcmp(list[index].name, "") != 0) {
    /* print their info */
    cout << list[index].name << "\t$" << list[index].price << '\n'
         << list[index].description << '\n'
         << "Rating: " << list[index].rating << " out of 5\n"
         << "----------------------" << endl;

    /* increment position */
    ++index;
  }
}


/* prints all available commands */
void helpCommand() {
  /* print the commands in a formatted way. */
  cout << "Available commands area:\n"
       << '\t' << "create   : creates a new pizza" << "\n"
       << '\t' << "search   : searches for a specific pizza" << "\n"
       << '\t' << "display  : display all pizzas" << "\n"
       << '\t' << "help     : print this help messgae" << "\n"
       << '\t' << "quit     : exit the program." << endl;
}

