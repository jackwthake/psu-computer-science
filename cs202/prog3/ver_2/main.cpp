#include "events.h"
#include "scheduler.h"

int main(void) {
  petting p("Petting zoo", 64, 30, 5.0f);
  p.add_animal_type(animal_type::pig);
  std::cout << p << std::endl;

  p += pig;
  std::cout << p << std::endl;
  p = p + horse;
  std::cout << p << std::endl;
  p -= pig;
  std::cout << p << std::endl;
  p = p - horse;
  std::cout << p << std::endl;

  return 0;
}
