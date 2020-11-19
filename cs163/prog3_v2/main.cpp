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

/* read in one item */
void read_in_item(CS_item_info &res) {
  char name[51], location[51], hints[51];
  cout << "Please enter the name of the item: ";
  cin.get(name, 51, '\n');
  cin.ignore(100, '\n');
  cout << "Please enter the location of the item: ";
  cin.get(location, 51, '\n');
  cin.ignore(100, '\n');
  cout << "Please enter the hints of the item: ";
  cin.get(hints, 51, '\n');
  cin.ignore(100, '\n');

  res = CS_item_info(name, location, hints);
}


/* main loop */
void main_loop(CS_item_queue &queue, CS_item_table &table) {
  char conf = NULL;

  do { /* loop to find all items  */
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


/* main entry point for program */
int main(void) {
  char conf = NULL;
  CS_item_table table("items.dat");
  CS_item_queue queue("items.dat");

  cout << "Items loaded" << endl;
  cout << "Now going to quickly test insertion to both the queue and hash table." << endl;

  CS_item_info tmp;
  read_in_item(tmp);

  table.add_item(tmp);
  char *tmp_name = tmp.get_name();
  queue.enqueue(tmp_name);
  delete []tmp_name;

  main_loop(queue, table);
  return 0;
}
