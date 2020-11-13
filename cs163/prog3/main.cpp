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

#include <iostream>
using namespace std;

int main(void) {
  CS_item_info info("test", "location", "hint", 5), info2("tes2t", "location2", "hint2", 2);
  CS_item_info info3("hello", "there", "hint boy", 4);
  CS_item_queue queue;
  CS_item_table table(8);
  
  queue.enqueue(info);
  queue.enqueue(info2);
  table.add_item(info);
  table.add_item(info2);
  table.add_item(info3);
  table.display_all();
  table.remove_item("test");

  return 0;
}
