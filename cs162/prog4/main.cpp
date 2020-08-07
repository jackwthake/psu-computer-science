#include "input.h"
#include "pizza_list.h"

#include <iostream>
using namespace std;

int main(void) {
  pizza_list list;

  list.displ_all();
  list.remove_item("Cheese");
  list.displ_all();

  if(list.exists("test1"))
    cout << "exists" << endl;
  
  return EXIT_SUCCESS;
}
