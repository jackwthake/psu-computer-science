#include "events.h"
#include "bst.cpp"

#include <cstring>


template <class TREE_TYPE, class TYPE>
void binary_tree_interaction(TREE_TYPE &tree) {
  std::string key;
  int choice = 0;
  TYPE obj;

  std::cout << "Which tree of events would you like to interact with?" << std::endl;
  std::cout << " 1. Insert" << std::endl;
  std::cout << " 2. Remove" << std::endl;
  std::cout << " 3. Search" << std::endl;
  std::cout << " 4. Display" << std::endl;
  std::cout << " 5. Print thetree height" << std::endl;
  std::cout << "Please enter an option, 1-5" << std::endl;

  std::cin >> choice;
  std::cin.ignore(100, '\n');

  switch (choice) {
    case 1: // insert
      obj.input();
      tree.insert(obj);
      break;
    case 2: // remove
      std::cout << "Please enter the name of the event to remove: ";
      std::cin >> key;

      obj = TYPE(key.c_str(), 0, 0, 0.f);
      tree.remove(obj);
      break;
    case 3: // search
      break;
    case 4: // display
      tree.display_all();
      break;
    case 5: // print tree height
      std::cout << "Tree has a height of " << tree.get_height() << std::endl;
      break;
    default:
      std::cout << "Invalid option." << std::endl;
      break;
  }
}



int main(void) {
  char conf = 0;
  int choice = 0;

  binary_search_tree<petting, petting> p_events; 
  binary_search_tree<aquatic, aquatic> a_events; 
  binary_search_tree<safari, safari> s_events; 

  do {
    std::cout << "Which tree of events would you like to interact with?" << std::endl;
    std::cout << " 1. Petting events" << std::endl;
    std::cout << " 2. Aquatic events" << std::endl;
    std::cout << " 3. Safari events" << std::endl;
    std::cout << "Please enter an option, 1-3" << std::endl;

    std::cin >> choice;
    std::cin.ignore(100, '\n');

    if (choice >= 1 && choice <= 3) {
      if (choice == 1)
        binary_tree_interaction<binary_search_tree<petting, petting>, petting>(p_events);
      else if (choice == 2)
        binary_tree_interaction<binary_search_tree<aquatic, aquatic>, aquatic>(a_events);
      else if (choice == 3)
        binary_tree_interaction<binary_search_tree<safari, safari>, safari>(s_events);
    } else {
      std::cout << "Invalid option." << std::endl;
    }

    std::cout << "More to do? (y/n): " << std::endl;
    std::cin >> conf;
    std::cin.ignore(100, '\n');
  } while (tolower(conf) != 'n');

  return 0;
}
