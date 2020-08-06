#include "input.h"
#include <iostream>
using namespace std;

void get_input(const char *prompt, int &value) {
  cout << prompt;
  cin >> value;
  cin.ignore(100, '\n');
}

void get_input_phrase(const char *prompt, char *value, int length) {
  cout << prompt;
  cin.get(value, length, '\n');
  cin.ignore(100, '\n');
}

void get_input_word(const char *prompt, char *value) {
  cout << prompt;
  cin >> value;
  cin.ignore(100, '\n');
}
