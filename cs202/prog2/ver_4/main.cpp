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


/* input and add an assignment to the list */
void add_activity(activity_list &list) {
  int choice = 0;
  assignment a;
  in_person_class i;
  remote_assistance r;

  cout << "Activity types: " << endl;
  cout << " 1. Assignment \n" \
          " 2. In Person Lecture \n" \
          " 3. Remote Assistance Session(s)" << endl;
  get_input_int("Which option? (1-3): ", choice);

  switch(choice) {
    case 1: // add an assignment
      a.input();
      list.add_activity(a);
      break;
    case 2: // add an in person lecture
      i.input();
      list.add_activity(i);
      break;
    case 3: // add a remote assistane seesion
      r.input();
      list.add_activity(r);
      break;
    default:
      cout << "Error: Invalid input" << endl;
      break;
  }
}


/* handles DLL interactions with the user */
void DLL_interaction(activity_list &list, vector<assignment> &completed_assignments) {
  int choice = 0;
  char buf[31];
  string new_time, new_day;
  psu_activity *res;
  
  cout << "Current activity options: " << endl;
  cout << " 1. Add an activity \n" \
          " 2. Remove an activity \n" \
          " 3. Get an activity \n" \
          " 4. Display the lists \n" \
          " 5. Clear the lists \n" << endl;
  get_input_int("Which option? (1-5): ", choice);

  switch (choice) {
    case 1: // Add activity
      add_activity(list);
      break;
    case 2: // Remove an activity
      get_input_phrase("Please enter the name of the activity to remove: ", buf, 31);
      if (list.remove_activity(buf, completed_assignments))
          cout << "Activity removed." << endl;
      break;
    case 3: // Get an activity
      get_input_phrase("Please enter the name of the activity: ", buf, 31);
      res = list.get_activity(buf);
      
      if (res) {
        res->display();

        cout << "Attempting RTTI for remote_assistance class..." << endl;
        if (remote_assistance *rem = dynamic_cast<remote_assistance*>(res)) {
          get_input_phrase("Please enter the new meeting time (12:00pm): ", buf, 31);
          new_time = buf;
          get_input_phrase("Please enter the new meeting days (M or M/W): ", buf, 31);
          new_day = buf;

          rem->reschedule_meeting_time(new_time, new_day);
        } else {
          cout << "Object is not a remote_assistance instance." << endl;
        }
      }
      break;
    case 4: // display the lists
      list.display();
      break;
    case 5: // clear the lists
      list.clear_all();
      break;
    default:
      cout << "Error: invalid input" << endl;
      break;
  }
}


/* handles vector interactions with the user */
void vector_interaction(activity_list &list, vector<assignment> &completed_assignments) {
  int choice = 0;
  char buf[31];
  
  cout << "Past Assignment options: \n" \
          " 1. Forget an assignment \n" \
          " 2. Get an assignmnet \n" \
          " 3. Display the completed assignments \n" \
          " 4. Clear the completed assignments" << endl;
  get_input_int("Which option? (1-4): ", choice);

  switch (choice) {
    case 1: // forget an assignment
      break;
    case 2: // get an assignment
      get_input_phrase("Please enter the name of the assignment to retrieve: ", buf, 31);
      for (assignment &a : completed_assignments) {
        if (strcmp(a.get_name(), buf) == 0)
          a.display();
      }
      break;
    case 3: // display all assignments
      for (assignment &a : completed_assignments) {
        cout << "--------------" << endl;
        a.display();
      }
      break;
    case 4: // clear the completed assignments
      completed_assignments.clear();
      break;
    default:
      cout << "Error: Invalid input" << endl;
      break;
  }
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

  introduction();
  main_loop(activities, completed_assignments);

  return 0;
};

