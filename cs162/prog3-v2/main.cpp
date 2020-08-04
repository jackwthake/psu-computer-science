#include "pizza.h"
#include "file.h"
#include "commands.h"

#include <iostream>
using namespace std;

const int num_pizzas = 20;

void main_loop(pizza list[]);

int main(void) {
  pizza list[num_pizzas] = { 0 }; /* initialize the array, filling it with 0's */

  if(!read_file("pizza.txt", list, num_pizzas)) {
    cerr << "Failed to load data file. Exitting." << endl;
    return EXIT_FAILURE;
  }
  
  main_loop(list);

  if(!write_file("pizza.txt", list, num_pizzas)) {
    cerr << "Failed to write to data file. Exitting." << endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}


void main_loop(pizza list[]) {
  bool running = true;
  
  while(running) {
    int cmd_type = get_user_command();

    switch(cmd_type) {
      case cmd_create:
        createCommand(list, num_pizzas);
        break;
      case cmd_search:
        searchCommand(list, num_pizzas);
        break;
      case cmd_display:
        displayCommand(list, num_pizzas);
        break;
      case cmd_help:
        helpCommand();
        break;
      case cmd_quit:
        running = !running;
        break;
      default:
        cout << "Unrecognized command." << endl;
        break;
    }
  } 
}
