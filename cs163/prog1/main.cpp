/*
 * Jack Thake, CS163, 10.3.20
 * This file holds the test program for this assignment.
*/

#include <iostream>

#include "CS_project_list.h"
#include "CS_project.h"

using namespace std;

int main(int argc, char const *argv[]) {
  CS_project_list list;
  CS_project project = { 0 };

  cout << "Success = " << SUCCESS << endl;
  cout << "Failure = " << FAILURE << endl;
  cout << "Memory allocation failure = " << MEM_ALLOC_FAIL << endl;

  cout << list.add_item(project) << endl;
  cout << list.add_item(project) << endl;
  cout << list.add_item(project) << endl;
  cout << list.add_item(project) << endl;

  cout << list.display() << endl;

  return 0;
}
