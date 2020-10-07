/*
 * Jack Thake, CS163, 10.3.20
 * This file holds the test program for this assignment.
*/

#include <iostream>

#include "CS_project_manager.h"
#include "CS_project_list.h"
#include "CS_project.h"

using namespace std;

CS_project project = {
  "name",
  "none",
  0
};

CS_project project2 = {
  "name2",
  "none",
  0
};

int main(int argc, char const *argv[]) {
  CS_project_list list;
  CS_project_manager manager;

  cout << "Success = " << SUCCESS << endl;
  cout << "Failure = " << FAILURE << endl;
  cout << "Memory allocation failure = " << MEM_ALLOC_FAIL << endl;

  cout << "List tests" << endl;
  cout << "Add item: " << list.add_item(project) << endl;
  cout << "Add item: " << list.add_item(project2) << endl;
  cout << "display items: " << list.display() << endl;
  cout << "Remove item: " << list.remove_item("name2") << endl;
  cout << "display items: " << list.display() << endl;

  cout << "Manager Tests" << endl;
  cout << "Display empty list: " << manager.display_all() << endl;
  cout << "Add priority: " << manager.add_priority(10) << endl;
  cout << "Add priority: " << manager.add_priority(15) << endl;
  cout << "Display populated list: " << endl << manager.display_all() << endl;

  return 0;
}
