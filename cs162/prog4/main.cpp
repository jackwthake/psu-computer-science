#include "input.h"
#include "pizza_list.h"

#include <iostream>
using namespace std;

int main(void) {
  pizza_list list;

  list.add_pizza();
  list.add_pizza();

  list.displ_most_recent();
  list.displ_all_with_rating(3);

  if(list.exists("test1"))
    cout << "exists" << endl;
  

  return EXIT_SUCCESS;
}
