//
//  main.cpp
//  psu-computer-science
//
//  Created by Jack Thake on 11/10/2020.
//  This file holds the test program
//

#include "CS_item_info.h"
#include "CS_item_queue.h"

#include <iostream>
using namespace std;

int main(void) {
  CS_item_info info("test", "location", "hint", 5), info2("tes2t", "location2", "hint2", 2);
  CS_item_info info3;
  CS_item_queue queue;

  queue.enqueue(info);
  queue.enqueue(info);
  queue.enqueue(info2);
  queue.display();
  queue.dequeue(info3);
  queue.display();

  return 0;
}
