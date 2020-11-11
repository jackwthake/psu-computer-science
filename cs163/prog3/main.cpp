//
//  main.cpp
//  psu-computer-science
//
//  Created by Jack Thake on 11/10/2020.
//  This file holds the test program
//

#include "CS_item_info.h"

#include <iostream>
using namespace std;

int main(void) {
  CS_item_info info("test", "location", "hint", 5), info2;
  info.print();

  info = info2;

  if (info == info2)
    cout << "works" << endl;

  return 0;
}
