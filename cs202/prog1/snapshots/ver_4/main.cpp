#include <iostream>

#include "location.h"
#include "gate.h"
#include "plane.h"
#include "ground_vehicle.h"
#include "vehicle_manager.h"

int main(void) {
  location l1(45.9, 43.2), l2(l1);
  vehicle v1(nullptr, 24, 25), v2(v1);;
  ground_vehicle gv1(refueler, 1, 2, true), gv2(gv1);;
  plane p1(nullptr, "PDX", 972, 400), p2(p1);
  gate g1("E5"); //g2(g1); <-- at the moment the copy constructor causes a runtime fault

  g1.enqueue_flight(p1);
  g1.enqueue_flight(p2);
  g1.enqueue_flight(p2);
  g1.enqueue_flight(p2);
  g1.enqueue_flight(p2);
  g1.enqueue_flight(p2);

  plane test = g1.get_flight_info(972);

  g1.land_flight();
  g1.land_flight();
  g1.land_flight();
  g1.land_flight();
  g1.land_flight();
  g1.land_flight();
  g1.land_flight();


  return 1;
}
