#include "CS_alert.h"

int main(int argc, char **argv) {
  CS_alert alert1, alert2("KGW", "10/18/20", "5:36 PM", "North korea launches nukes at world");
  CS_alert_stack stack;
  
  alert1 = alert2;

  stack.push(alert2);
  stack.push(alert2);
  stack.push(alert2);
  stack.push(alert2);

  stack.display();

  return 0;
}
