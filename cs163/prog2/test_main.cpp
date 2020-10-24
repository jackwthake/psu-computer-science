#include "CS_alert.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
  CS_alert alert1("ABC", "10/23/20", "8:16 AM", "Damn bro that's crazy");
  CS_alert alert2("KGW", "10/18/20", "5:36 PM", "North korea launches nukes at world");
  CS_alert alert3;
  CS_alert_stack stack;
  
  stack.push(alert2);
  stack.push(alert1);
  stack.push(alert2);
  stack.display();
  cout << endl << endl;

  cout << "first pop results:" << endl;
  stack.pop(); /* should pop top of stack */
  stack.display(); /* should display two item */
  cout << "second pop results:" << endl;
  stack.pop(); /* remove second to last item */
  stack.display(); /* shouldnt display one item */
  cout << "third pop results:" << endl;
  stack.pop(); /* shouldnt do anything */
  stack.display(); /* shouldnt do anything */

  return 0;
}
