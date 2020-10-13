/*
 * Jack Thake, CS163, 10.3.20
 * This file holds the test program for this assignment.
*/

#include <iostream>

#include "CS_project_manager.h"
#include "CS_project_list.h"
#include "CS_project.h"

/* if this is defined then the user will need to enter values to test the program. */
#define USER_TEST

using namespace std;

int main(int argc, char const *argv[]) {
  struct tm when;
  char date[9];
  get_time_val_from_string("1/18/03", when);
  get_time_string_from_int(date, &when);
  cout << date << endl;

#ifdef USER_TEST
  cout << "-- CS_project_list Project Tests --" << endl;
  cout << "-- CS_project_list Display Tests --" << endl;

  cout << "-- CS_project_manager Priority Tests --" << endl;
  cout << "-- CS_project_manager Project Tests --" << endl;
  cout << "-- CS_project_manager Display Tests --" << endl;
#else
#endif
  return 0;
}
