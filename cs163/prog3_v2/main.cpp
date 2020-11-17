#include "CS_item_queue.h"
#include "CS_item_info.h"

#include <cstdlib>
#include <fstream>
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
  ifstream data;
  data.open("items.dat");
  
  CS_item_info info(data), info2;
  data.close();
  
  info.print();
  info2 = info;

  CS_item_queue queue("items.dat");
  main_loop(queue);
  return 0;
}

