#include "events.h"
#include "bst.cpp"

int main(void) {
  std::string region = "Savannah";
  std::string guide = "Me";

  std::list<animal_type> types;
  std::list<safari> matches;

  types.push_back(lion);
  std::pair<std::string, std::list<animal_type>>  pair = std::make_pair(region, types);
  safari p("aquarium", guide, 64, 30, 5.0f);
  binary_search_tree<safari, safari> tree, tree2;
  tree.insert(p);

  tree2 = tree;
  tree2.display_all();

  return 0;
}
