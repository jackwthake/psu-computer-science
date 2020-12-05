/*
 * Jack Thake, Karla Fant, CS163
 * This file holds the test program.
*/

#include <cstring>
#include <iostream>
#include "graph.h"

using namespace std;

/* entry point */
int main (void) {
  char conf = '\0', temp[51], temp2[51];
  int len = 0;

  cout << "Follow prompts to add courses to the graph" << endl << endl;
  
  cout << "Please enter the desired length of the graph: ";
  cin >> len;
  cin.ignore(100, '\n');

  graph test(len);

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

  cout << "Folow the prompts, entering in course names you already added to the program, the program will then print all courses you can take after completing the entered course." << endl;

  do {
    cout << "Please enter course name: ";
    cin.get(temp, 51, '\n');
    cin.ignore(100, '\n');

    test.display(temp);

    cout << endl << "More to display? (y/n): ";
    cin >> conf;
    cin.ignore(100, '\n');
  } while (tolower(conf) != 'n');

  cout << "Now destroying the graph, using the destructor." << endl;
  return 0;
}

