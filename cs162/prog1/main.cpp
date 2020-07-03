/*
 * Jack Thake
 * June 27, 2020
 * CS162
 *
 * This program prompts the user to enter in when their shift starts, any breaks
 * that may of happened, and then their clock out time. It then prints out a
 * small report on how much time they worked.
 *
 * Coded entirely in vim :D
*/

#include <cmath> // used for floor()
#include <iostream>
using namespace std;

/*
 * Function Prototypes
*/

// Input functions
int getTime(string message);

// Output functions
void printTime(int hour, int minutes);
void printTimeReport(int timeWorked, int breakTime);
void printTimeNotes(int timeWorked);



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
  int tempHour, tempMinute; // tempHour holds the hour inputted, ie 8 or 15 etc, tempMinute holds the minute in the hour, ie 15 or 35 etc
  char tempDivider; // used to capture the ':' character when the times are inputted
  string confirmation; // holds the user's responce when being asked for confirmation 

  do {
    // Prompting for input
    cout << message;
    cin >> tempHour >> tempDivider >> tempMinute; // get the time like 9:00 as an example
    cin.ignore(100, '\n'); // clear input buffer

    // Confirmation
    cout << "You entered: ";
    printTime(tempHour, tempMinute); // print the formatted time back to the user for confirmation
    cout << ", is that value correct? [yes/no]: ";
    
    // recieve the confirmation from the user
    cin >> confirmation;
    cin.ignore(100, '\n'); // clear input buffer
  } while("yes" != confirmation); // exit when the user confirms the input

  return (tempHour * 60) + tempMinute; // convert the hours to minutes and add the minutes in the hour, then return
}



/*
 * printTime(int hout, int minutes)
 *
 * brief: this function takes the hour an minute and prints a formatted time
 *
 * hour: holds the hour of the time to be printed
 * minutes: holds the amount of minutes to be printed
 */
void printTime(int hour, int minutes) {
  cout << hour << ":";
  
  if(0 == minutes)
    cout << "00";
  else
    cout << minutes;
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

  /*
   * Now we print the time report
   *
   * floor(time / 60) = hours
   * time % 60 = minutes in the hour
  */

  cout << endl << "============================= Time Report =============================" << endl;

  cout << "All times in Hour:Minute." << endl;

  cout << "Gross Time Worked: ";
  printTime(floor(grossTimeWorked / 60), grossTimeWorked % 60); // print the formatted time
  cout << endl;

  cout << "Net Time Worked: ";
  printTime(floor(netTimeWorked / 60), netTimeWorked % 60); // print the formatted time
  cout << endl;
  
  cout << "Time spent in breaks(s): ";
  printTime(floor(breakTime / 60), breakTime % 60); // print the formatted time
  cout << endl;

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
  
  if(floor(timeWorked / 60) > 6) // get the hours worked and check if they're over 6
    cout << "You should've taken a lunch break." << endl;

  if(floor(timeWorked / 60) > 8) // get the hours worked and check if they're over 8
    cout << "You should be careful about overtime, be sure to have authorization from your boss." << endl;
  
  cout << "============================ End of Notes =============================" << endl << endl;
}



int main(void) {
  int clockInTime = 0, clockOutTime = 0; // These two hold the clock in time and the clock out time of the user
  int breakTime = 0; // breakTime holds the amount of break time the user entered
  string confirmation = ""; // Used for confirming a user submission
  
  // welcome user
  cout << "Welcome to the hour tracking software, please input the correct times in 24 hour formatting when prompted.";
  cout << endl << "The program will then print a report to the screen displaying how much time you worked." << endl << endl;

  // get the shift start
  clockInTime = getTime("Please enter your clock in time: "); 
  cout << endl;

  // loop to input all breaks the user may have taken
  do {
    cout << "Is there a break to be inputted? [yes/no]: ";
    cin >> confirmation;
    cin.ignore(100, '\n'); // clear input buffer

    if("yes" == confirmation) {
      // prompt the user for the start and end of the break
      int breakStart = getTime("Please enter the time your break started: ");
      int breakEnd = getTime("Please enter the time your break ended: ");
      cout << endl;

      // get the length of the break and add it to the breakTime counter
      breakTime += breakEnd - breakStart;
    } 
  } while("no" != confirmation); // loop until the user is done inputting breaks

  // get the shift end
  clockOutTime = getTime("Please enter your clock out time: "); 

  // Calculate times and print them out
  printTimeReport(clockOutTime - clockInTime, breakTime);

  // Print notes on worked time
  printTimeNotes(clockOutTime - clockInTime);

  // return to operating system
  return 0;
}
