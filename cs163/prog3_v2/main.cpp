#include "CS_item_queue.h"

#include <cstdlib>
#include <iostream>
using namespace std;

int main(void) {
  CS_item_queue queue("items.dat");
  queue.print_all();

  return 0;
}

