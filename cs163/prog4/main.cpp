#include "video_entry.h"
#include "video_tree.h"
#include <iostream>
using namespace std;

int main(void) {
  video_entry entry("class", "abc", "discription", 5, "next");
  video_entry entry2("CLASS", "def", "discription", 5, "next");
  video_tree tree;


  tree.insert(entry2);
  tree.insert(entry);
  cout << tree.get_height() << endl;
  tree.display_course("class");
  tree.display_all();

  return 0;
}
