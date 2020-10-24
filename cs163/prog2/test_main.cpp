#include "CS_alert.h"

int main(int argc, char **argv) {
  CS_alert alert1("ABC", "10/23/20", "8:16 AM", "Damn bro that's crazy");
  CS_alert alert2("KGW", "10/18/20", "5:36 PM", "North korea launches nukes at world");
  CS_alert alert3;
  CS_alert_stack stack;
  
  stack.push(alert2);
  stack.push(alert1);
  stack.push(alert2);
  stack.push(alert1);

  stack.display();
  stack.peak(alert3);
  alert3.display();

  return 0;
}
