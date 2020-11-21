#include "video_entry.h"
#include <iostream>
using namespace std;

int main(void) {
  video_entry entry("class", "media", "discription", 5, "next"), empty;
  empty.print();
  return 0;
}
