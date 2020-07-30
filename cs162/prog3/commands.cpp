/*
 * Jack Thake
 * CS162, Program 3, July 29th, 2020
 *
 * This file holds all implementations of the user input related functions from
 * commands.h
*/


#include "commands.h"

#include "pizza.h"
#include <cstring>
#include <iostream>
using namespace std;



/*
 * void get_input_value(const char *prompt, int &value)
 *
 * brief: prints out the prompt value, reads in one value from the user.
 *
 * const char *prompt: the prompt to be displayed to the user
 * int &value: the variable to be set with the user's input
*/
void get_input_value(const char *prompt, int &value) {
  cout << prompt; /* print prompt to user */
  
  /* read in value */
  cin >> value;

  /* flush input buffer */
  cin.ignore(100, '\n');  
}



/*
 * void get_input_value(const char *prompt, float &value)
 *
 * brief: prints out the prompt value, reads in one value from the user.
 *
 * const char *prompt: the prompt to be displayed to the user
 * float value: the variable to be set with the user's input
*/
void get_input_value(const char *prompt, float &value) {
  cout << prompt; /* print prompt to user */
  
  /* read in value */
  cin >> value;

  /* flush input buffer */
  cin.ignore(100, '\n');  
}



/*
 * void get_input(const char *prompt, char *res, int len)
 *
 * brief: prints out the prompt value, than reads in the user's input into the
 *        response string
 *
 * const char *prompt: the text to be displayed to the user.
 * char *res: the response from the user.
 * int len: the maximum length of the response.
*/
void get_input(const char *prompt, char *res, int len) {
  cout << prompt; /* print prompt to user  */

  /* respect array bounds while recieving input */
  cin.width(len);
  cin.get(res, len, '\n');

  /* flush input buffer */
  cin.ignore(100, '\n');
}


/*
 * int get_user_command(void)
 *
 * brief: prompts the user to enter a command, returns the correct type of
 *        command the user entered
 *
 * return: returns the corresponding enum value for the user-entered comman.
*/
int get_user_command(void) {
  char cmd[cmd_size]; /* buffer for the command to be stored in */
  get_input("Please enter a command: ", cmd, cmd_size); /* prompt the user, recieve input into the buffer */

  /* test which command was entered, returning the corresponding enum value */
  if(strcmp(cmd, "create") == 0) 
    return cmd_type_create; /* create command */
  if(strcmp(cmd, "search") == 0)
    return cmd_type_search; /* search command */
  if(strcmp(cmd, "display") == 0)
    return cmd_type_display; /* display command */
  if(strcmp(cmd, "help") == 0)
    return cmd_type_help; /* help command */
  if(strcmp(cmd, "quit") == 0)
    return cmd_type_quit; /* quit command */
  else
    return cmd_type_unknown; /* unknown command */
}


/*
 * void create_command(list &data)
 *
 * brief: executes the create command, adding one node to the passed list.
*/
void create_command(list &data) {
  Pizza pizza; /* the struct that will be added */

  /* read in the Pizza's members */
  get_input("Please enter the name of the pizza: ", pizza.name, field_length);
  get_input("Please enter a description for the pizza: ", pizza.description, field_length);
  get_input("Please enter any extra toppings: ", pizza.additions, field_length);
  get_input("Please enter any removals from the pizza: ", pizza.removals, field_length);
  get_input_value("\nPlease enter a rating out of 5 for the pizza: ", pizza.rating);
  get_input_value("Please enter the price of the pizza: $", pizza.price);

  /* add the pizza to the list */
  data.add(pizza);
}



/*
 * void search_command(list &data)
 *
 * brief: executes the search command, searches the list for a given pizza's
 *        name, displays the pizza if found.
*/
void search_command(list &data) {
  char search_name[field_length]; /* buffer for the name of the pizza */
  const Pizza *result; /* the result of the search */

  /* get the name of the pizza from the user */
  get_input("Please enter the pizza's name that you are searching for: ", search_name, field_length);

  /* search the list for the name, storing the result */
  result = data.exists(search_name);

  if(result != NULL) { /* if the result isn't NULL then a pizza was found, print it's members. */
    std::cout << endl
              << "------- Result -------\n"
              << "Name: " << result->name << "\n"
              << "Description: " << result->description << "\n"
              << "Additions: " << result->additions << "\n"
              << "Removals: " << result->removals << "\n"
              << "Rating (Out of 5): " << result->rating << "\n" 
              << "Price: " << result->price << "\n" 
              << "----------------------\n" << endl;
  } else /* no pizza was found with that name. */
    cout << "No pizza was found that matched that name." << endl;
}



/*
 * void display_command(list &data)
 *
 * brief: executes the display command, prints out all list nodes.
*/
void display_command(list &data) {
  data.display_all(); /* print the list's nodes */
}



/*
 * void help_command()
 *
 * brief: executes the help command, prints all available commands.
*/
void help_command() {
  /* print the commands in a formatted way. */
  cout << "Available commands area:\n"
       << '\t' << "create   : creates a new pizza" << "\n"
       << '\t' << "search   : searches for a specific pizza" << "\n"
       << '\t' << "display  : display all pizzas" << "\n"
       << '\t' << "help     : print this help messgae" << "\n"
       << '\t' << "quit     : exit the program." << endl;
}
