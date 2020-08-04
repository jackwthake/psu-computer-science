#include "commands.h"
#include <iostream>
using namespace std;


static void get_input(const char *prompt, int &value) {
  cout << prompt; /* print prompt to user */
  
  /* read in value */
  cin >> value;

  /* flush input buffer */
  cin.ignore(100, '\n');  
}


static void get_input(const char *prompt, char *res, int len) {
  cout << prompt; /* print prompt to user  */

  /* respect array bounds while recieving input */
  cin.width(len);
  cin.get(res, len, '\n');

  /* flush input buffer */
  cin.ignore(100, '\n');
}


static void refine_command(char *cmd, char *refined) {
  int i, j = 0;
  for(i = 0; i < strlen(cmd); ++i) {
    if(!isspace(cmd[i])) {
      refined[j] = tolower(cmd[i]);
      ++j;
    }
  }

  refined[j] = '\0';
}


int get_user_command(void) {
  char buf[cmd_size]; /* buffer for the command to be stored in */
  char cmd[cmd_size];
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


void createCommand(pizza list[], int length) {
  int index = 0;

  while(strcmp(list[index].name, "") != 0)
    ++index;

  if(index < length) {
    get_input("Please enter the pizza's name: ", list[index].name, field_length);
    get_input("Please enter the pizza's description: ", list[index].description, field_length);
    get_input("Please enter the pizza's additions: ", list[index].additions, field_length);
    get_input("Please enter the pizza's removals: ", list[index].removals, field_length);
    get_input("Please enter the pizza's price: $", list[index].price, price_length);
    get_input("Please enter the pizza's rating out of 5: ", list[index].rating);
  } else {
    cout << "Max number of pizzas have already been created." << endl;
  }
}


void searchCommand(pizza list[], int length) {
  int index = 0;
  char tester[field_length];

  get_input("Please enter the search name: ", tester, field_length);

  while(strcmp(list[index].name, "") != 0) {
    if(strcmp(list[index].name, tester) == 0) {
      cout << "----------------------" << endl;
      cout << list[index].name << "\t$" << list[index].price << '\n'
           << list[index].description << '\n'
           << "Rating: " << list[index].rating << " out of 5\n"
           << "----------------------" << endl;
      
      return;
    }

    ++index;
  }

  cout << "No result found with that name." << endl;
}


void displayCommand(pizza list[], int length) {
  int index = 0;
  
  cout << "----------------------" << endl;

  while(strcmp(list[index].name, "") != 0) {
    cout << list[index].name << "\t$" << list[index].price << '\n'
         << list[index].description << '\n'
         << "Rating: " << list[index].rating << " out of 5\n"
         << "----------------------" << endl;

    ++index;
  }
}


void helpCommand() {
  /* print the commands in a formatted way. */
  cout << "Available commands area:\n"
       << '\t' << "create   : creates a new pizza" << "\n"
       << '\t' << "search   : searches for a specific pizza" << "\n"
       << '\t' << "display  : display all pizzas" << "\n"
       << '\t' << "help     : print this help messgae" << "\n"
       << '\t' << "quit     : exit the program." << endl;
}

