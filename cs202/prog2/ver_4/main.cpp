/*
 * Jack Thake
 * Karla Fant
 * CS202
 * main.cpp
 *
 * This file holds the test program. THe test program needs to properly interface with the data structure
 * allowing the user to add, remove, get, display, and clear the DLL of activities. If when an activity
 * of the type assignment is removed from the list, It should be pushed onto a vector that holds completed
 * assignments, Interfacing with the vector needs to be able to add completed assignments, print all completed
 * assignments, get a specific completed assignment, and "forget" an assignment which will act as a removal.
 * The interaction with the vector will be more behind the scenes in terms of addition, as a completed assignment
 * will be automatically pushed into the vector when it get's removed from the DLL.
*/

#include <iostream>
#include <vector>
#include <cstring>

/* class headers */
#include "assignment.h"
#include "in_person_class.h"
#include "remote_assistance.h"
#include "DLL.h"

/* helper */
#include "input.h"

using namespace std;


/* prints out a greating */
void introduction(void) {
  cout << "Welcome to the PSU activity manager. This program helps keep track of ongoing assignments, \n" \
       << "in person sessions as well as remote assistance sessions such as office hours. Each \n" \
       << "activity has a priority from 0-4, with 0 being the most important tasks." << endl << endl;
}


/* handles DLL interactions with the user */
void DLL_interaction(activity_list &list, vector<assignment> &completed_assignments) {
  cout << "DLL interaction" << endl;
}


/* handles vector interactions with the user */
void vector_interaction(activity_list &list, vector<assignment> &completed_assignments) {
  cout << "vector interaction" << endl;
}


/* main loop */
void main_loop(activity_list &list, vector<assignment> &completed_assignments) {
  int choice = 0;
  char conf = '\0';

  do {
    // print options
    cout << "Would you like to interact with:" << endl << "1. current activities" << endl << "2. passed assignments" << endl;
    // get input
    get_input_int("option 1 or 2? ", choice); 

    // check if input is valid
    if (choice < 1 || choice > 2) {
      cout << "Error, option requested does not exist." << endl;
    } else {
      if (choice == 1) // invoke the appropriate interaction
        DLL_interaction(list, completed_assignments);
      else
        vector_interaction(list, completed_assignments);
    }

    cout << endl << "More to do? (y/n)" << endl;
    cin >> conf;
    cin.ignore(100, '\n');
  } while (tolower(conf) != 'n');
}


/* main entry point */
int main(void) {
  activity_list activities; // holds all current activities
  vector <assignment>completed_assignments; // holds all past assignments

  assignment a1("10/12/21", "homework 4", 2);
  activities.add_activity(a1);
  activities.remove_activity(a1, completed_assignments);

  introduction();
  main_loop(activities, completed_assignments);

  return 0;
};

