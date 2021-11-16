#include "events.h"
#include "scheduler.h"

int main(void) {
  std::string region = "Savannah";
  std::string guide = "Me";

  animal_type types[3] = { lion, leopard, girrafe };
  safari p("aquarium", guide, 64, 30, 5.0f);

  p.add_region(region, types, 3);
  p.display_all_regions();


  return 0;
}
