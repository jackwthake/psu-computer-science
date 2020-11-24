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
  tree.insert(entry2);
  tree.insert(entry2);
  
  video_entry *arr = NULL;
  int len = 0;
  tree.search("def", arr, len);

  for (int i = 0; i < len; ++i) {
    arr[i].print();
  }

  cout << tree.get_height() << endl;
  delete []arr;

  return 0;
}
