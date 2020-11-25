#include "video_entry.h"
#include "video_tree.h"
#include <iostream>
using namespace std;

int main(void) {
  video_entry entry("class", "5", "discription", 5, "next");
  video_entry entry2("CLASS2", "2", "discription", 5, "next");
  video_entry entry3("CLASS2", "8", "discription", 5, "next");
  video_entry entry4("CLASS2", "6", "discription", 5, "next");
  video_tree tree;


  tree.insert(entry);
  tree.insert(entry2);
  tree.insert(entry3);
  tree.insert(entry4);
  tree.insert(entry);

  tree.remove_course("CLASS2");
  tree.display_all();

  return 0;
}
