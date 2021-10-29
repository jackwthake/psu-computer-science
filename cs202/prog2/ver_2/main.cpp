#include "psu_activity.h"

int main(void) {
  psu_activity act("test name", 1, 2), act2(act), act3;
  act3.set_name("test time");
  act.set_name("test two");

  return 0;
};
