//
//  main.cpp
//  psu-computer-science
//
//  Created by Jack Thake on 11/10/2020.
//  This file holds the test program
//

#include "CS_item_info.h"
#include "CS_item_queue.h"
#include "CS_item_table.h"

#include <fstream>
#include <iostream>
using namespace std;

int main(void) {
  ifstream file;
  file.open("items.dat");
  CS_item_table table(file);
  table.display_all();

  file.close();

  return 0;
}
