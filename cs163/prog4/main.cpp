#include "video_entry.h"
#include "video_tree.h"
#include <iostream>
using namespace std;

int main(void) {
  video_entry entry("class", "media", "discription", 5, "next");
  video_tree tree;


  tree.insert(entry);
  tree.insert(entry);
  tree.insert(entry);

  return 0;
}
