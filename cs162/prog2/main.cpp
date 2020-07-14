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

const int MAX_WORD = 21;

struct word {
  int start_pos, end_pos;
  char data[MAX_WORD];
};

/*
 * Function prototypes
*/
void read_into_buffer(const char prompt[], char response[], int response_size);
void tokenize_string(const char str[], int str_size, word tokens[]);

/*
 * Function definitions
*/

/*
 * read_into_buffer(const char prompt[], char response[], int response_size)
 *
 * brief: prints the characters in the prompt array, and awaits the users input,
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

/*
 * tokenize_string(const char str[], int str_size, word tokens[])
 *
 * brief: takes a string, splits it into a list of words
 * str[]: the string to be split into words
 * str_size: length of string not including terminating null
 * tokens[]: an array of word structs each containing one of the words in the
 *           passed string
*/
void tokenize_string(const char str[], int str_size, word tokens[]) {
  int current_word = 0;
  bool word_started = false;

  for(int i = 0; i < str_size; ++i) {
    if(!isblank(str[i]))  {  /* Don't care about spaces or blank characters  */ 
      if((i == 0 || isblank(str[i - 1])) && !word_started) { /* find the first character of a word, the first character will always be treated as the start of the first word */
        tokens[current_word].start_pos = i;
        word_started = true;
      }

      if(i == str_size - 1 || isblank(str[i + 1])) { /* find the end of the word, respecting the array bounds  */
        tokens[current_word].end_pos = i;
        
        /* 
         * Copy the word into the word struct
        */
        for(int j = 0; j <= tokens[current_word].end_pos - tokens[current_word].start_pos; ++j) {
          tokens[current_word].data[j] = str[tokens[current_word].start_pos + j];
        }

        /* add the terminating null character  */
        tokens[current_word].data[tokens[current_word].end_pos - tokens[current_word].start_pos + 1] = '\0';

        /* get ready for the next word */
        word_started = false;
        ++current_word;
      }
    }
  }
}

int main(void) {
  /* test code */
  char buf[48];
  word tokens[12];
  
  read_into_buffer("Enter something: ", buf, 48);
  cout << buf << endl;

  tokenize_string(buf, strlen(buf), tokens);

  for(int i = 0; i < 12; i++) {
    cout << tokens[i].start_pos << " " << tokens[i].end_pos << " " << tokens[i].data << endl;
  }

  return EXIT_SUCCESS;
}

