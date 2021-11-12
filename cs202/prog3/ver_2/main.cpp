#include "events.h"
#include "scheduler.h"

int main(void) {
  aquatic p("aquarium", 64, 30, 5.0f);
  std::cout << p << std::endl;

  std::string tester = "Penguin";
  p.add_exhibit(tester, penguin);
  std::cout << p << std::endl;

  return 0;
}
