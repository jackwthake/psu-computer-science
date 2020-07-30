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
      case cmd_type_create:
        create_command(pizzas);
        break; 
      case cmd_type_search:
        search_command(pizzas);
        break; 
      case cmd_type_display:
        display_command(pizzas);
        break; 
      case cmd_type_help:
        help_command();
        break; 
      case cmd_type_quit:
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
