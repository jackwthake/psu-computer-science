#include "input.h"
#include "pizza_list.h"

#include <iostream>
using namespace std;

int main(void) {
  pizza_list list("pizza.txt");

  list.displ_all();

  if(list.exists("test1"))
    cout << "exists" << endl;
  
  return EXIT_SUCCESS;
}
