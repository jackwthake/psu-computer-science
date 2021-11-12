#include "events.h"
#include "scheduler.h"

int main(void) {
  event ev("petting zoo", 64, 30, 5.0f), ev2(ev), ev3;

  ev3 = ev;

  std::string str("Fun");
  std::string str2("Fun2");

  try {
    ev.display_reviews();
  } catch (std::string s) {
    std::cout << s << std::endl;
  }

  std::cout << ev << std::endl;
  std::cin >> ev;

  ev.add_review(str);
  ev.add_review(str2);
  ev.add_review(str);
  ev.add_review(str);
  ev.add_review(str2);
  ev.add_review(str2);
  ev.display_reviews();
  
  try {
    ev2.display_reviews();
  } catch (std::string s) {
    std::cout << s << std::endl;
  }

  try {
    ev3.display_reviews();
  } catch (std::string s) {
    std::cout << s << std::endl;
  }
  return 0;
}
