#include <iostream>
using namespace std;

#include "list.h"
#include "pizza.h"
#include "commands.h"


void introduction(void);


int main(void) {
  list pizzas("pizza.txt");
  bool running = true;

  introduction();

  while(running) {
    switch(get_user_command()) {
      case command_type::command_create:
        create_command(pizzas);
        break; 
      case command_type::command_search:
        search_command(pizzas);
        break; 
      case command_type::command_display:
        display_command(pizzas);
        break; 
      case command_type::command_help:
        help_command();
        break; 
      case command_type::command_quit:
        running = false;
        break; 
      default:
        cout << "Unknown command." << endl;
        break;
    }
  }

  cout << "Quitting..." << endl;
  pizzas.write_list_to_file("pizza.txt");

  return 1;
}



void introduction(void) {
  cout << "Welcome to the number 1 Pizza keep-tracker!" << endl;

  help_command();
}
