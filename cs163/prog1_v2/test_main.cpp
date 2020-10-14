//
//  test_main.cpp
//  psu-computer-science
//
//  Created by Jack Thake on 13/10/2020.
//  This file holds the entry point to the test program
//

#include <iostream>
#include "CS_project.h"
using namespace std;

int main(int argc, char const *argv[]) {
  CS_project project;
  CS_project project2("test", "test", "ads", 1, 1, 1);

  cout << project.display() << endl;
  cout << project2.display() << endl;

  project = project2;
  cout << project.display() << endl;

  return 0;
}
