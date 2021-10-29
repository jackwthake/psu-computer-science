#include "psu_activity.h"

int main(void) {
  psu_activity act("test name", 1, 2), act2(act), act3;

  return 0;
};
