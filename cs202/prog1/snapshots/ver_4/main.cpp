#include <iostream>

#include "location.h"
#include "gate.h"
#include "plane.h"
#include "ground_vehicle.h"
#include "vehicle_manager.h"

int main(void) {
  location l1(45.9, 43.2), l2(l1);
  vehicle v1(nullptr, 24, 25), v2(v1);;
  ground_vehicle gv1(refueler, 1, 2, true), gv2(unknown, 1, 2, true), gv3(lavatory, 1, 2, true);
  plane p1(nullptr, "PDX", 972, 400), p2(p1);
  gate g1("E5"); //g2(g1); <-- at the moment the copy constructor causes a runtime fault
  vehicle_manager vm;

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

  vm.add_to_pool(gv1);
  vm.add_to_pool(gv2);
  vm.add_to_pool(gv3);

  const ground_vehicle *gv = vm.get_vehicle_from_pool(refueler);

  vehicle_type arr[2] = {
    refueler,
    unknown
  };

  vm.request_vehicles(&g1, arr, 2);
  vm.release_vehicles(&g1);

  vm.remove_from_pool(gv1);
  vm.remove_from_pool(gv2);
  vm.remove_from_pool(gv3);

  vm.clear_pool();

  return 1;
}
