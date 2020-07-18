#include <iostream>
#include <ctype.h>
#include <cstring>
#include <time.h>
using namespace std;

/* prototypes */
void prompt_user_input(const char *prompt, char *response, unsigned response_length);
void clear_term();
void embed_word(const char *word, char *phrase);
char rand_alpha();

/* constants */
const unsigned SECRET_LENGTH = 11;
const unsigned PHRASE_LENGTH = 101;

int main(int argc, char **argv) {
  /* initialise secret_word and phrase */
  char secret_word[SECRET_LENGTH];
  char phrase[PHRASE_LENGTH];

  /* read in the phrase and word */
  prompt_user_input("Please enter the secret word: ", secret_word, SECRET_LENGTH);
  prompt_user_input("Please enter the phrase: ", phrase, PHRASE_LENGTH);

  /* clear screen */
  clear_term();

  /* print out the phrase and word */
  cout << secret_word << endl;
  cout << phrase << endl;

  embed_word(secret_word, phrase);

  cout << phrase << endl;

  return 0;
}


/*
 * void prompt_user_input(const char *prompt, char *response, unsigned response_length)
 *
 * brief: prompts user for input, reads in the entered text and stores it.
 *
 * prompt: text to be printed to the user
 * response: location where the user's response will be stored
 * response_length: length of response's memory block
*/
void prompt_user_input(const char *prompt, char *response, unsigned response_length) {
  cout << prompt;

  cin.width(response_length); /* respect array bounds */
  cin.get(response, response_length, '\n'); /* read in */
  cin.ignore(100, '\n'); /* clear input buffer */
}


/*
 * void clear_term()
 *
 * brief: clears the terminal screen in a non-platform specific way.
*/
void clear_term() {
  for (int i = 0; i < 200; ++i) {
    cout << '\n';
  }

  cout << endl;
}


/*
 * void embed_word(const char *word, char *phrase)
 *
 * brief: hides a word into the phrase
 *
 * word: word to be hidden
 * phrase: phrase to hide the word in
*/
void embed_word(const char *word, char *phrase) {
  int counter = 0; /* holds number of characters since the last space */
  int cur_word_char = 0; /* holds the current character needing to be embedded */
  bool has_word_editted = false;

  /* loop through string */
  for (int i = 0; i < strlen(phrase); ++i) {
    if(isspace(phrase[i])) { /* check if current char is a space */
      counter = 0; /* reset chars since last space */
      has_word_editted = false; /* reset for the next word */
    } else {
      if(counter == cur_word_char && !has_word_editted) { /* check if were looking at the right character in the word */
        if(!isupper(phrase[i])) { /* make sure the character is lowercase */
          phrase[i] = word[cur_word_char]; /* replace the character */
          ++cur_word_char; /* increment which character in the word we're working with */
          has_word_editted = true; /* don't keep editting this word */
        }
      }

      ++counter; /* one more character without hitting a space */
    }

    /* check for the underscore rule */
    if(phrase[i] == '_')
      phrase[i] = rand_alpha(); /* set to random character */
  }
}


/*
 * char rand_alpha()
 *
 * brief: returns a random lowercase letter
 *
 * return: random lowercase letter
*/
char rand_alpha() {
  srand(time(NULL));

  /*
   * we use this formula to create a range, from 97 ('a') to 122 ('z') on the
   * ascii table.
  */
  return (rand() % (122 - 97 + 1)) + 97;
}
