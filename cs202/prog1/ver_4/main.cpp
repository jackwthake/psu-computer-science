#include <iostream>

#include "gate.h"
#include "plane.h"
#include "ground_vehicle.h"
#include "vehicle_manager.h"


/* read user input */
void prompt_user(const char *prompt, const int length, char *response) {
  std::cout << prompt;
  std::cin.get(response, length, '\n');
  std::cin.ignore(100, '\n');
}


void setup(vehicle_manager &manager) {
  // populate vehicle manager with some vehicles
  // make 3 of each vehicle type
  for (int i = 0; i < 3; ++i) {
    ground_vehicle veh(refueler);
    manager.add_to_pool(veh);
  }
  
  for (int i = 0; i < 3; ++i) {
    ground_vehicle veh(lavatory);
    manager.add_to_pool(veh);
  }

  for (int i = 0; i < 3; ++i) {
    ground_vehicle veh(air_starter);
    manager.add_to_pool(veh);
  }
}


/*
 * Print out all the gates and their vehicles
*/
void print_gates_and_vehicles(vehicle_manager &manager, gate *gate_arr) {
  // display gate numbers
  std::cout << "Available gates: " << std::endl;
  for (int i = 0; i < 3; ++i) {
    std::cout << "---" << std::endl;
    gate_arr[i].display();
  }

  std::cout << std::endl << std::endl;

  manager.display();
}


int main(void) {
  // array of LLL
  gate gate_arr[3] = {
    gate("A1"),
    gate("A2"),
    gate("A3")
  };

  // CLL
  vehicle_manager manager;

  setup(manager);
  print_gates_and_vehicles(manager, gate_arr);

  return 1;
}
