//
//  test_main.cpp
//  psu-computer-science
//
//  Created by Jack Thake on 13/10/2020.
//  This file holds the entry point to the test program
//

#include <iostream>
#include <cstring>
#include "CS_project.h"
using namespace std;

int main(int argc, char const *argv[]) {
  CS_project project("name", "workers", "date", 1, 1, 1);
  CS_project p("name2", "workers 2", "date 2", 2, 2, 2);

  project.display();
  p.display();
  p = project;
  p.display();

  return 0;
}
