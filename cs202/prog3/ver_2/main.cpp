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


  petting p("Petting zoo", 64, 30, 5.0f);
  p.add_animal_type(animal_type::pig);
  std::cout << p << std::endl;

  return 0;
}
