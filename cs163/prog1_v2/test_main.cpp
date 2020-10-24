//
//  test_main.cpp
//  psu-computer-science
//
//  Created by Jack Thake on 13/10/2020.
//  This file holds the entry point to the test program, I'm sorry the test code
//  is pretty messy - I'm pretty sure it tests for all cases.
//

#include <iostream>
#include <cstring>
#include "CS_project.h"
using namespace std;


/* prompts the user and recieves input */
static void prompt_user(const char *prompt, int max_length,  char *response) {
  cout << prompt;
  cin.get(response, max_length, '\n');
  cin.ignore(100, '\n');
}


/* reads in info for one project and populates the passed object */
static void read_in_project(CS_project &project) {
  char name[21], workers[21], date[10];
  float cost;
  int days, coolness;

  prompt_user("Please enter the project name: ", 21, name);
  prompt_user("Please enter the project workers: ", 21, workers);
  prompt_user("Please enter the project's completion date (MM/DD/YY): ", 9, date);

  cout << "Enter the estimated cost: $";
  cin >> cost;
  cin.ignore(100, '\n');
  cout << "Enter the project's length in days: ";
  cin >> days;
  cin.ignore(100, '\n');
  cout << "Enter the project's coolness from 0 to 5: ";
  cin >> coolness;
  cin.ignore(100, '\n');

  project = CS_project(name, workers, date, cost, days, coolness);
}


/* tests out the CS_project class */
static void CS_project_tests() {
  CS_project project, unpopulated, unpopulated_2;

  /* test out inputting and displaying an object */
  cout << endl << endl << "Please enter all prompted values" << endl;
  read_in_project(project);
  cout << endl << endl << "attempting to print newly created object - should succeed." << endl;
  if (project.display() == SUCCESS)
    cout << "Test Succeeded" << endl;
  else
    cout << "Test Failed" << endl;

  cout << endl << endl << "attempting to print unpopulated object - should fail." << endl;
  if (unpopulated.display() == FAILURE)
    cout << "Test Succeeded" << endl;
  else
    cout << "Test Failed" << endl;

  cout << endl << endl << "assigning populated object to unpopulated object" << endl;
  unpopulated = project;
  cout << "attempting to print the now populated object - should succeed" << endl;
  if (unpopulated.display() == SUCCESS)
    cout << "Test Succeeded" << endl;
  else
    cout << "Test Failed" << endl;

  cout << endl << endl << "now attempting to assign an empty object to an initialized one" << endl;
  project = unpopulated_2;
  cout << endl << endl << "now attempting to print what should now be an empty object - should fail" << endl;
  if (project.display() == FAILURE)
    cout << "Test Succeeded" << endl;
  else
    cout << "Test Failed" << endl;
}


static void CS_project_list_tests() {
  CS_project_list list;
  CS_project tmp;
  char conf = 0;
  char name[21];

  cout << endl << endl << "Display unpopulated list - should fail" << endl;
  if (list.display() == FAILURE)
    cout << "Print Failed, Test successful." << endl;
  else
    cout << "Print Succeeded, Test Failed" << endl;

  cout << endl << endl << "Now attempting to add projects to the list, enter the prompted values." << endl;
  do {
    read_in_project(tmp);
    if (list.add_project(tmp) == SUCCESS)
      cout << "Addition successful." << endl;
    else
      cout << "Addition failed." << endl;

    cout << "Are there more to add? (y/n): ";
    cin >> conf;
    cin.ignore(100, '\n');
  } while(tolower(conf) != 'n');

  list.display();

  cout << endl << endl << "Now attempting to remove projects from the list, enter the prompted values." << endl;
  do {
    prompt_user("Enter the name of an existing object to remove: ", 21, name);
    if (list.remove_project(name) == SUCCESS)
      cout << "Removal successful." << endl;
    else
      cout << "Removal failed." << endl;

    cout << "Are there more to remove? (y/n): ";
    cin >> conf;
    cin.ignore(100, '\n');
  } while(tolower(conf) != 'n');

  cout << endl << endl << "Now attempting to print the list" << endl;
  list.display();

  cout << endl << endl << "Now attempting to remove non existing projects, enter the prompted values." << endl;
  prompt_user("Enter the name of a non existing object to try and remove - should fail: ", 21, name);
  if (list.remove_project(name) == FAILURE)
    cout << "Removal Failed, Test successful." << endl;
  else
    cout << "Removal Succeeded, Test Failed" << endl;
}


static void CS_project_manager_tests() {
  CS_project project;
  CS_project_manager manager;
  char name[21], conf = 0;
  int priority = 0;

  cout << endl << endl << "Attempting to display all priorities in an empty list - should fail" << endl;
  if (manager.display() == FAILURE)
    cout << "Print Failed, Test successful." << endl;
  else
    cout << "Print Succeeded, Test Failed" << endl;

  cout << endl << endl << "Attempting to display non-existing priority - should fail" << endl;
  if (manager.display(0) == FAILURE)
    cout << "Print Failed, Test successful." << endl;
  else
    cout << "Print Succeeded, Test Failed" << endl;

  cout << endl << endl << "Now add priority lists, entering more than one of the same priority should fail." << endl;
  do {
    cout << "Please enter a priority to be added (whole number): ";
    cin >> priority;
    cin.ignore(100, '\n');

   if (manager.add_priority(priority) == SUCCESS)
     cout << "Priority added successfully." << endl;
   else
     cout << "Priority failed to be added." << endl;

    cout << "Are there more priorities to add? (y/n): ";
    cin >> conf;
    cin.ignore(100, '\n');
  } while (tolower(conf) != 'n');


  cout << endl << endl << "Now add projects to priority lists. trying to add a list to a non-existing priority should fail. leave atleast one list unpopulated for the next test." << endl;
  do {
    cout << "Please enter a priority to be added (whole number): ";
    cin >> priority;
    cin.ignore(100, '\n');
    read_in_project(project);

   if (manager.add_project(priority, project) == SUCCESS)
     cout << "Project added successfully." << endl;
   else
     cout << "Project failed to be added." << endl;

    cout << "Are there more projects to add? (y/n): ";
    cin >> conf;
    cin.ignore(100, '\n');
  } while (tolower(conf) != 'n');

  cout << endl << endl << "Attempting to display all priorities, when (atleast) one list is unpopulated - should fail" << endl;
  if (manager.display() == FAILURE)
    cout << "Print Failed, Test successful." << endl;
  else
    cout << "Print Succeeded, Test Failed" << endl;


  cout << endl << endl << "Now remove projects from priority lists. trying to remove a non-existing prject should fail." << endl;
  do {
    prompt_user("Please enter the name of a project to remove: ", 21, name);

   if (manager.remove_project(name) == SUCCESS)
     cout << "Project removed successfully." << endl;
   else
     cout << "Project failed to be removed." << endl;

    cout << "Are there more projects to remove? (y/n): ";
    cin >> conf;
    cin.ignore(100, '\n');
  } while (tolower(conf) != 'n');

  cout << endl << endl << "Attempting to display all priorities, when (atleast) one list is unpopulated - should fail" << endl;
  if (manager.display() == FAILURE)
    cout << "Print Failed, Test successful." << endl;
  else
    cout << "Print Succeeded, Test Failed" << endl;


  cout << endl << endl << "Now remove any empty priority lists, for the next test. trying to remove a non-existing priority should fail." << endl;
  do {
    cout << "Please enter a priority to be removed (whole number): ";
    cin >> priority;
    cin.ignore(100, '\n');

   if (manager.remove_priority(priority) == SUCCESS)
     cout << "Priority removed successfully." << endl;
   else
     cout << "Priority failed to be removed." << endl;

    cout << "Are there more priorities to remove? (y/n): ";
    cin >> conf;
    cin.ignore(100, '\n');
  } while (tolower(conf) != 'n');

  cout << endl << endl << "Attempting to display all priorities, with all lists populated - should succeed" << endl;
  if (manager.display() == FAILURE)
    cout << "Print Succeeded, Test successful." << endl;
  else
    cout << "Print Failed, Test Failed" << endl;

  cout << endl << endl << "Lastly enter one existing priority to display: ";
  cin >> priority;
  cin.ignore(100, '\n');
  manager.display(priority);
}

int main(int argc, char const *argv[]) {
  cout << "CS_project class tests" << endl;
  CS_project_tests();
  cout << endl << endl << "CS_project_list class tests" << endl;
  CS_project_list_tests();
  cout << endl << endl << "CS_project_manager class tests" << endl;
  CS_project_manager_tests();

  return 0;
}
