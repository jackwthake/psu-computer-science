#include "CS_alert.h"

#include <cstring>
#include <iostream>
using namespace std;


void prompt_user(const char *prompt, const int length, char *response) {
  cout << prompt;
  cin.get(response, length, '\n');
  cin.ignore(100, '\n');
}


void read_in_alert(CS_alert &alert) {
  char org[31], date[11], time[11], message[201];
  
  prompt_user("Please enter the organization: ", 31, org);
  prompt_user("Please enter the date (dd/mm/yy): ", 11, date);
  prompt_user("Please enter the time: (hh/mm AM/PM)", 31, time);
  prompt_user("Please enter the message: ", 201, message);

  alert = CS_alert(org, date, time, message);
}


int main(int argc, char **argv) {
  bool running = true;
  char resp[4];
  int command = 0, ret = FAILURE;

  CS_alert temp;
  CS_alert_stack stack;

  cout << "Welcome. This should test out my stack data structure, it will attempt to display" <<
          " the contents of the stack at the beggining of every iteration, entering a number" <<
          " from 1 to 3 selects a command for that given iteration, at the end a" <<
          " message is printed stating whether the operation was successful, or if an error" <<
          " occured, and if so what kind. Thank you and happy grading! :)" << endl;

  /* main loop */
  do {
    /* display current stack to user */
    cout << endl << endl << "Displaying current stack:" << endl;
    if (stack.display() == FAILURE)
      cout << "\tEmpty stack." << endl;

    /* display user options */
    cout << endl << "Please enter one of the following numbers:" << endl;
    cout << "1. push to the stack" << endl;
    cout << "2. pop from the stack" << endl;
    cout << "3. peack from the stack" << endl;
    cout << "Please enter aone of the above numbers: ";
    cin >> command;
    cin.ignore(100, '\n');

    /* do the selected comand */
    switch (command) {
      case 1: /* push command */
          cout << "Push to top of stack" << endl;
          read_in_alert(temp);
          ret = stack.push(temp);
        break;
      case 2: /* pop command */
          cout << "Popping top of stack." << endl;
          ret = stack.pop();
        break;
      case 3: /* peak command */
          cout << "Peak top of stack" << endl;
          ret = stack.peak(temp);
          if (ret == SUCCESS)
            temp.display();
        break;
      default:
        cout << "No command recognized." << endl;
        break;
    }

    /* check return value, print accordingly */
    if (ret == FAILURE)
      cout << "Operation failed" << endl;
    else if (ret == MEM_ALLOC_ERROR)
      cout << "Memory failed to be allocated" << endl;
    else if (ret == SUCCESS)
      cout << "Operation successful" << endl;

    /* prompt user weather there is more to do */
    cout << endl;
    prompt_user("Is there more to do? (yes/no): ", 4, resp);
    if (strcmp(resp, "no") == 0)
      running = false;
  } while (running);

  return 0;
}
