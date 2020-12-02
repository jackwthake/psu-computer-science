#include <cstring>
#include <iostream>
#include "graph.h"

using namespace std;

int main (void) {
  char conf = '\0', temp[51], temp2[51];
  graph test;

  cout << "Follow prompts to add courses to the graph" << endl << endl;

  do {
    cout << "Please enter course name: ";
    cin.get(temp, 51, '\n');
    cin.ignore(100, '\n');

    test.insert_course(temp);

    cout << "More to add? (y/n): ";
    cin >> conf;
    cin.ignore(100, '\n');
  } while (tolower(conf) != 'n');
  
  cout << "Follow prompts to add connections to the graph" << endl << endl;
  cout << "Enter in two course names, which have already been added to the graph, in the following format: cs162,cs163" << endl;
  cout << "This will add cs163 to cs162's list of connections. Note: don't add a space after the comma." << endl;

  do {
    cout << "Please enter two courses separated by commas: ";
    cin.get(temp, 51, ',');
    cin.ignore(100, ',');
    cin.get(temp2, 51, '\n');
    cin.ignore(100, '\n');

    if (!test.insert_edge(temp, temp2)) {
      cout << "Failed to connect requested vertices, at least one does not exist." << endl;
    } else {
      cout << "vertices connected." << endl;
    }

    cout << "More to connect? (y/n): ";
    cin >> conf;
    cin.ignore(100, '\n');
  } while (tolower(conf) != 'n');

  test.display("cs162");

  return 0;
}

