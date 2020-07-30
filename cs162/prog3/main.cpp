#include <iostream>
using namespace std;

#include "list.h"
#include "pizza.h"



/*
 * void get_input(const char *prompt, char *res, int len)
 *
 * brief: prints out the prompt value, than reads in the user's input into the
 *        response string
 *
 * const char *prompt: the text to be displayed to the user.
 * char *res: the response from the user.
 * int len: the maximum length of the response.
*/
void get_input(const char *prompt, char *res, int len) {
  cout << prompt; /* print prompt to user  */

  /* respect array bounds while recieving input */
  cin.width(len);
  cin.get(res, len, '\n');

  /* flush input buffer */
  cin.ignore(100, '\n');
}



/*
 * void get_input_value(const char *prompt, T &value)
 *
 * brief: prints out the prompt value, reads in one value from the user, using
 *        the passed type. The reason why I am using templates is just to limit
 *        code duplication, this makes it far cleaner in terms of the
 *        implementation.
 *
 * const char *prompt: the prompt to be displayed to the user
 * T &value: the variable to be set with the user's input
*/
template <typename T>
void get_input_value(const char *prompt, T &value) {
  cout << prompt; /* print prompt to user */
  
  /* read in value */
  cin >> value;

  /* flush input buffer */
  cin.ignore(100, '\n');  
}



int main(void) {
  list pizzas("pizza.txt");

  cout << "first print" << endl;
  pizzas.display_all();

  pizzas.write_list_to_file("pizza.txt");

  char test[12];
  int test2;

  get_input("string of text: ", test, 12);
  get_input_value("value test: ", test2);

  cout << test << endl << test2 << endl;;

  return 1;
}
