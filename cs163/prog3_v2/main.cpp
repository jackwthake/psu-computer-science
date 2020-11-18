/*
 * This file holds the test program for program 3
*/

#include "CS_item_queue.h"
#include "CS_item_table.h"
#include "CS_item_info.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;


void main_loop(CS_item_queue &queue, CS_item_table &table) {
  char conf = NULL;

  do {
    cout << "Print hash table contents? (y/n): ";
    cin >> conf;
    if (tolower(conf) == 'y')
      table.print_all();


    cout << "Queue contents" << endl;
    cout << "  | Items still to be found" << endl;
    queue.print_all();

    cout << "Lookup current front of queue? (y/n): ";
    cin >> conf;

    if (tolower(conf) == 'y') {
      CS_item_info tmp;

      char *key = queue.peak();
      table.retrieve(key, tmp);
      delete []key;

      tmp.print();
    }

    cout << "Found Current Item? - First on the list - (y/n): ";
    cin >> conf;

    if (tolower(conf) == 'y') {
      char *key = queue.peak();
      table.remove_item(key);
      queue.dequeue();
      delete []key;
    }
  } while (!queue.is_empty());
}


int main(void) {
  CS_item_table table("items.dat");
  CS_item_queue queue("items.dat");

  main_loop(queue, table);
  return 0;
}
