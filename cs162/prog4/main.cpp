/*
 * Jack Thake, Program 4, Aug 8, 2020
 * CS162
 *
 * This program is the imporved program from program 3, it keeps track of user
 * entered pizzas inside of a data file, and uses a sorted linear linked list
 * this file holds the program's entry point as well as all of the code to
 * handle commands.
*/

#include "input.h"
#include "pizza_list.h"

#include <cstring>
#include <iostream>
using namespace std;

/* converts a string to all lower case */
void to_lower_str(char *str) {
  for(unsigned i = 0; i < strlen(str); ++i) {
    str[i] = tolower(str[i]);
  }
}


/* sets up the remove item command  */
void remove_item(pizza_list &list) {
  char name[field_length];
  get_input_phrase("Enter the name of the pizza to be deleted: ", name, field_length);

  list.remove_item(name);
}


/* set up the print all with rating command */
void print_all_with_rating(pizza_list &list) {
  int rating = 0;
  get_input("Enter the rating to search for: ", rating);

  list.displ_all_with_rating(rating);
}


/* sets up the search command */
void search(pizza_list &list) {
  char name[field_length];
  get_input_phrase("Enter the name of the pizza to be searched for: ", name, field_length);
  pizza *result = list.exists(name);

  if(result) {
    print_pizza(*result);
  } else {
    cout << "No pizza found" << endl;
  }
}


/* prints out all available commands */
void help() {
  cout << "Pizza tracking software 2.0 by Jack Thake \n"
       << "\tcreate\t\tAdds one pizza to the list.\n"
       << "\tsearch\t\tSearches for a given pizza\n\n"
       << "\tremove\t\tRemoves a given pizza\n"
       << "\tclear\t\tDeletes everything in the list\n\n"
       << "\tprint\t\tPrints all pizzas in alphabetical order\n"
       << "\tprint recent\tPrints most recently added pizza\n"
       << "\tprint rating\tPrints all with a given rating\n\n"
       << "\thelp\t\tPrints this help message" << endl;
}


/* entry point */
int main(void) {
  pizza_list list; /* Linear Linked List of all pizzas */
  char command[31]; /* Holds the current user entered command */

  /* prints all available commands on startup */
  help();

  do {
    /* prompt user for a command, convert it to lowercase */
    get_input_phrase("Please enter a command: ", command, 31);
    to_lower_str(command);

    /* decide which command was entered */
    if(strcmp(command, "create") == 0)
      list.add_pizza(); /* create command */
    else if(strcmp(command, "search") == 0)
      search(list); /* search command */
    else if(strcmp(command, "remove") == 0)
      remove_item(list); /* remove a specific item */
    else if(strcmp(command, "clear") == 0)
      list.clear_list(); /* delete list */
    else if(strcmp(command, "print") == 0)
      list.displ_all(); /* display all alphabetically */
    else if(strcmp(command, "print rating") == 0)
      print_all_with_rating(list); /* print all with rating */
    else if(strcmp(command, "print recent") == 0)
      list.displ_most_recent(); /* display most recent addition to list*/
    else if(strcmp(command, "help") == 0)
      help(); /* print commands */
    else if(strcmp(command, "quit") != 0) /* we only do this so it doesn't print quit as unrecognized */
      cout << "No recognized command entered." << endl;
  } while(strcmp(command, "quit")); /* exit if user enters quit */

  cout << "Exitting" << endl;

  return EXIT_SUCCESS;
}
