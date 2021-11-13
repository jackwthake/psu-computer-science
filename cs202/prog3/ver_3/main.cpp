#include "events.h"
#include "scheduler.h"

int main(void) {
  aquatic p("aquarium", 64, 30, 5.0f);
  std::cout << p << std::endl;

  std::string tester = "Penguin";
  p += make_pair(tester, pig);
  std::cout << p << std::endl;
  p -= make_pair(tester, pig);
  std::cout << p << std::endl;
  p = p + make_pair(tester, horse);
  std::cout << p << std::endl;
  p = p - make_pair(tester, horse);

  return 0;
}
