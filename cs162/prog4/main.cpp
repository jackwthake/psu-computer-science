#include "input.h"
#include "pizza_list.h"

#include <cstring>
#include <iostream>
using namespace std;

static void to_lower_str(char *str) {
  for(int i = 0; i < strlen(str); ++i) {
    str[i] = tolower(str[i]);
  }
}

void remove_item(pizza_list &list) {
  char name[field_length];
  get_input_phrase("Enter the name of the pizza to be deleted: ", name, field_length);

  list.remove_item(name);
}

void print_all_with_rating(pizza_list &list) {
  int rating = 0;
  get_input("Enter the rating to search for: ", rating);

  list.displ_all_with_rating(rating);
}

void search(pizza_list &list) {
  char name[field_length];
  get_input_phrase("Enter the name of the pizza to be deleted: ", name, field_length);
  pizza *result = list.exists(name);

  if(result) {
    print_pizza(*result);
  } else {
    cout << "No pizza found" << endl;
  }
}

void help() {
  cout << "Pizza tracking software 2.0 by Jack Thake \n"
       << "\tcreate\t\tAdds one pizza to the list.\n"
       << "\tsearch\t\tSearches for a given pizza\n\n"
       << "\tremove\t\tRemoves a given pizza\n"
       << "\tclear\t\tDeletes everything in the list\n\n"
       << "\tprint\t\tPrints all pizzas in alphabetical order\n"
       << "\tprint recent\tPrints most recently added pizza\n"
       << "\tprint rating\tPrints all with a given rating\n\n" 
       << "\thelp\t\tPrints this help message" << endl;  
}

int main(void) {
  pizza_list list;
  char command[31];

  help();

  do { 
    get_input_phrase("Please enter a command: ", command, 31);
    to_lower_str(command);

    if(strcmp(command, "create") == 0)
      list.add_pizza();
    else if(strcmp(command, "search") == 0)
      search(list);
    else if(strcmp(command, "remove") == 0)
      remove_item(list);
    else if(strcmp(command, "clear") == 0)
      list.clear_list();
    else if(strcmp(command, "print") == 0)
      list.displ_all();
    else if(strcmp(command, "print rating") == 0)
      print_all_with_rating(list);
    else if(strcmp(command, "print recent") == 0)
      list.displ_most_recent();
    else if(strcmp(command, "help") == 0)
      help();
  } while(strcmp(command, "quit"));

  return EXIT_SUCCESS;
}

