#include <iostream>

#include "location.h"
#include "gate.h"
#include "plane.h"
#include "ground_vehicle.h"
#include "vehicle_manager.h"

int main(void) {
  location l1, l2(45.9, 43.2);
  vehicle v1;
  ground_vehicle gv1;
  plane p1;
  plane p2(nullptr, "PDX", 972, 400);

  return 1;
}
