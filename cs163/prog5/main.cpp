#include <cstring>
#include <iostream>
#include "graph.h"

using namespace std;

int main (void) {
  char conf = '\0', temp[51];
  graph test;

  do {
    cout << "Please enter course name: ";
    cin.getline(temp, 51, '\n');
    cin.ignore(100);

    test.insert_course(temp);

    cout << "More to add? (y/n): ";
    cin >> conf;
    cin.ignore(100, '\n');
  } while (tolower(conf) != 'n');

  return 0;
}
