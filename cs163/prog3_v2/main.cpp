#include "CS_item_queue.h"

#include <cstdlib>
#include <iostream>
using namespace std;

int main(void) {
  CS_item_queue queue;

  queue.enqueue("test");
  char *res = queue.peak();
  queue.dequeue();

  cout << res << endl;
  delete []res; 

  return 0;
}

