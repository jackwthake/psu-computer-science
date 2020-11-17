#include "CS_item_queue.h"

#include <cstdlib>
#include <iostream>
using namespace std;


void main_loop(CS_item_queue &queue) {
  char conf = NULL;

  do {
    cout << "  | Items still to be found" << endl;
    queue.print_all();

    cout << "Found Current Item? - First on the list - (y/n): ";
    cin >> conf;

    if (tolower(conf) == 'y') {
      queue.dequeue();
    }
  } while (!queue.is_empty()); 
}


int main(void) {
  CS_item_queue queue("items.dat");
  main_loop(queue);
  return 0;
}

