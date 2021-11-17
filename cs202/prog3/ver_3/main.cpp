#include "events.h"
#include "bst.h"

int main(void) {
  std::string region = "Savannah";
  std::string guide = "Me";

  std::list<animal_type> types;
  types.push_back(lion);
  std::pair<std::string, std::list<animal_type>>  pair = std::make_pair(region, types);
  safari p("aquarium", guide, 64, 30, 5.0f);

  std::cout << p << std::endl;
  p += pair;
  std::cout << p << std::endl;
  p -= pair;
  std::cout << p << std::endl;
  p = p + pair;
  std::cout << p << std::endl;
  p = p - pair;
  std::cout << p << std::endl;



  return 0;
}
