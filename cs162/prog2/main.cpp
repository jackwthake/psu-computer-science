#include <iostream>
#include <ctype.h>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
using namespace std;

/* prototypes */
void prompt_user_input(const char *prompt, char *response, unsigned response_length);
void clear_term();
char rand_alpha();
void word_to_lower(char *str);

void introduce_player();
void embed_word(const char *word, char *phrase);

/* constants */
const unsigned SECRET_LENGTH = 11;
const unsigned PHRASE_LENGTH = 101;
const unsigned MAX_SCORE = 3;


int main(void) {
  /* initialise secret_word and phrase */
  char secret_word[SECRET_LENGTH];
  char phrase[PHRASE_LENGTH];
  char guess[SECRET_LENGTH];
  char prompt[129];

  /* game variables */
  int turn = 1, round = 1;
  unsigned player_1_score = 0, player_2_score = 0;

  /* introduce rules */
  introduce_player();

  while(player_1_score < MAX_SCORE && player_2_score < MAX_SCORE) {
    /* print out the score and which player should be guessing */
    cout << "Score: P1: " << player_1_score << " | P2: " << player_2_score << " | Round " << round << '\n'
         << "It is currently Player " << turn << "'s turn hiding a word." << endl;

    /* get the secret word from the player */
    sprintf(prompt, "Player %d please enter your secret word while the other player looks away:\n", turn);
    prompt_user_input(prompt, secret_word, SECRET_LENGTH);

    /* get the phrase from the player */
    sprintf(prompt, "Player %d please enter your phrase while the other player continues to looks away:\n", turn);
    prompt_user_input(prompt, phrase, PHRASE_LENGTH);

    /* clear the screen */
    clear_term();
    /* embed the word */
    embed_word(secret_word, phrase);

    /* tell guessor the phrase */
    cout << "Guessing player may now look at the screen.\n\nThe phrase to guess from is:\n"
         << phrase << endl;
    /* get the guesser's guess */
    prompt_user_input("Guessing player please enter your guess:\n", guess, SECRET_LENGTH);

    if(strcmp(guess, secret_word) == 0) { /* increment the guessers score if they're correct */
      turn == 1 ? ++player_2_score : ++player_1_score;
      cout << guess << " was correct!" << endl;
    } else {
      turn == 1 ? ++player_1_score : ++player_2_score; /* increment the hider's score otherwise */
      cout << guess << " was wrong :(" << endl;
    }

    turn == 1 ? turn = 2 : turn = 1; /* switch the turn */
    ++round; /* increment the round */

    cout << endl << endl << endl;
  }

  /* print the final score */
  cout << "Game Over!\nFinal score was: P1: " << player_1_score << " | P2: " << player_2_score << endl;

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


/*
 * void word_to_lower(char *str)
 *
 * brief: converts word to fully lowercase
 *
 * str: string to be set to all lowercase
*/
void word_to_lower(char *str) {
  int len = strlen(str);

  for (int i = 0; i < len; ++i) {
    str[i] = tolower(str[i]);
  }
}


/*
 * void introduce_player()
 *
 * brief: introduces the rules to the players
*/
void introduce_player() {
  cout << "Welcome to word hider!\n"
       << "In this game each player takes turns either guessing or hiding words.\n"
       << "As a guesser your job is to guess the word the hider has hidden.\n"
       << "Each round the guesser guesses right their score increases by one and\n"
       << "the same for the hider, once a player reaches a score of " << MAX_SCORE << " the game ends.\n"
       << "At the end of each round roles are swapped. The rules for how the program\n"
       << "hides words are as follows: \n"
       << "  1. Each word gets one character embedded into it, the nth word gets the nth\n"
       << "     character, ie. the second character goes in the second words second\n"
       << "     character, and so on.\n"
       << "  2. If a word in the player entered phrase is all capitalized we skip the word\n"
       << "     not embedding any characters into that word.\n"
       << "  3. If a word is not long enough to embed the current character the word gets\n"
       << "     skipped and has no character stored in it.\n"
       << "  4. If an underscore is encountered, a random character will be inserted" << endl << endl;
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
  unsigned len = strlen(phrase);
  int counter = 0; /* holds number of characters since the last space */
  int cur_word_char = 0; /* holds the current character needing to be embedded */
  bool has_word_editted = false;

  /* loop through string */
  for (unsigned i = 0; i < len; ++i) {
    if(isspace(phrase[i])) { /* check if current char is a space */
      counter = 0; /* reset chars since last space */
      has_word_editted = false; /* reset for the next word */
    } else {
      if(counter == cur_word_char && !has_word_editted) { /* check if we're looking at the right character in the word */
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

  /* convert phrase to lowercase */
  word_to_lower(phrase);
}
