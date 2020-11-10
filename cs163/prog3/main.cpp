#include "CS_item_info.h"

#include <iostream>
using namespace std;

int main(void) {
  CS_item_info info("test", "location", "hint", 5);
  info.print();

  if (info == info)
    cout << "works" << endl;

  return 0;
}
