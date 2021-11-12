#include "events.h"
#include "scheduler.h"

int main(void) {
  event ev("petting zoo", 64, 30, 5.0f), ev2(ev);
  return 0;
}
