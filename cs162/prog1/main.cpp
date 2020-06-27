/*
 * Jack Thake
 * June 27, 2020
 * CS162
*/

#include <cmath>
#include <iostream>
using namespace std;



/*
 * getTime(string message)
 *
 * brief: this function is passed a string holding a prompt that will be printed
 *        to the user, and awaits for the user to enter a time, and then returns
 *        the time in minutes entered by the user
 * 
 * message: message is the prompt to be displayed to the user
 *
 * return value: will return the time entered by the user converted to minutes
 *               since midnight.
*/
int getTime(string message) {
  int tempHour, tempMinute;
  char tempDivider;
  string confirmation; 

  do {
    // Prompting for input
    cout << message;
    cin >> tempHour >> tempDivider >> tempMinute;

    // Confirmation
    cout << "You entered: " << tempHour << ":" << tempMinute << ", is that value correct? [yes/no]: ";
    cin >> confirmation;
  } while("yes" != confirmation);

  return (tempHour * 60) + tempMinute;
}



/*
 *  printTimeReport(int timeWorked, int breakTime)
 *
 *  brief: this function is used to convert the times to a printable form and
 *         print them in an orderly way
 *
 *  timeWorked: this argument represents the duration of the time worked in
 *              minutes without taking away the time spent in breaks
 *
 *  breakTime: this argument represents the total time spent in a break in
 *             minutes
*/
void printTimeReport(int timeWorked, int breakTime) {
  int grossTimeWorked = timeWorked; // without taking breaktime away
  int netTimeWorked = timeWorked - breakTime; // with taking breaktime away

  cout << endl << "============================= Time Report =============================" << endl;
  cout << "Gross Time Worked: " << floor(grossTimeWorked / 60) << ":" << grossTimeWorked % 60 << endl;
  cout << "Net Time Worked: " << floor(netTimeWorked / 60) << ":" << netTimeWorked % 60 << endl;
  cout << "Time Spent in Break: " << floor(breakTime / 60) << ":" << breakTime % 60 << endl;
  cout << "========================= End of Time Report ==========================" << endl;
}



/*
 * printTimeNotes(int timeWorked)
 *
 * brief: this function takes the amount of minutes worked and decideds weather
 *        the user should have taken a lunch break or if the user has gone into 
 *        over time
 * 
 * timeWorked: the amount of time worked without taking breaks into
 *             consideration, stored in minutes
*/
void printTimeNotes(int timeWorked) {
  cout << endl << "================================ Notes ================================" << endl;
  
  if(floor(timeWorked / 60) > 6)
    cout << "You should've taken a lunch break." << endl;

  if(floor(timeWorked / 60) > 8)
    cout << "You should be careful about overtime, be sure to have authorization from your boss." << endl;
  
  cout << "============================ End of Notes =============================" << endl << endl;
}



int main(void) {
  int clockInTime = 0, clockOutTime = 0; // These two hold the clock in time and the clock out time of the user
  int breakTime = 0; // breakTime holds the amount of break time the user enteried
  string confirmation = ""; // Used for confirming a user submission
  
  // get the shift start
  clockInTime = getTime("Please enter your clock in time: "); 
  cout << endl;

  // loop to input all breaks the user may have taken
  do {
    cout << "Is there a break to be inputted? [yes/no]: ";
    cin >> confirmation;

    if("yes" == confirmation) {
      // prompt the user for the start and end
      int breakStart = getTime("Please enter the time your break started: ");
      int breakEnd = getTime("Please enter the time your break ended: ");
      cout << endl;

      // get the length of the break and add it to the breakTime counter
      breakTime += breakEnd - breakStart;
    } 
  } while("no" != confirmation);

  // get the shift end
  clockOutTime = getTime("Please enter your clock out time: "); 

  // Calculate times and print them out
  printTimeReport(clockOutTime - clockInTime, breakTime);

  // Print notes on worked time
  printTimeNotes(clockOutTime - clockInTime);

  return 0;
}
