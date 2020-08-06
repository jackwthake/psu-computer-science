#include "input.h"

#include <iostream>
using namespace std;

int main(void) {
  int test1;
  char long_test[21], short_test[11];

  get_input("enter in a number", test1);
  get_input_word("enter a word", short_test);
  get_input_phrase("enter phrase", long_test, 21);

  cout << test1 << endl << short_test << endl << long_test << endl;

  return EXIT_SUCCESS;
}
