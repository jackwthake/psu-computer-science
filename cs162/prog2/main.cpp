/*
 * Puzzle Game
 * Jack Thake
 * CS162, Program 2
 * July 8th, 2020
 *
 * I'm trying out underscores rather than camel case
 * Still coded only in vim :D
*/

#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;



/*
 * Function prototypes
*/
void read_into_buffer(const char prompt[], char response[], int response_size);



int main(void) {
  char buf[21];

  read_into_buffer("Enter something: ", buf, 21);
  cout << buf << endl;

  return EXIT_SUCCESS;
}



/*
 * Function definitions
*/

/*
 * read_into_buffer(const char prompt[], char response[], int response_size)
 *
 * breif: prints the characters in the prompt array, and awaits the users input,
 *        clearing the input buffer after the appropriate amount of input is collected
 * prompt: array of characters to be displayed to the user
 * response: array of characters that will be modified to hold the user's
 *           response
 * response_size: holds the size of the response array
*/
void read_into_buffer(const char prompt[], char response[], int response_size) {
  cout << prompt;
  cin.get(response, response_size, '\n');
  cin.ignore(100, '\n');
}
