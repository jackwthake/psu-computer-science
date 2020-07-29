#include <iostream>
using namespace std;

#include "list.h"
#include "pizza.h"

int main(void) {
  list pizzas("pizza.txt");

  cout << "first print" << endl;
  pizzas.display_all();

  pizzas.write_list_to_file("pizza.txt");

  return 1;
}
