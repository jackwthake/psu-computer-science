#include "input.h"
#include "pizza_list.h"

#include <iostream>
using namespace std;

int main(void) {
  pizza_list list;

  list.add_pizza();
  list.add_pizza();

  list.displ_most_recent();

  if(list.exists("test1"))
    cout << "exists" << endl;
  
  return EXIT_SUCCESS;
}
