#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* contains all of the words that the program will ask the user to type */
#define WORD_LENGTH 9
#define BUF_SIZE 10
static const char *words[WORD_LENGTH] = { "The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog" };

/* compare two strings appropriately */
int compare(const char *a, const char *b) {
    return strlen(a) == strlen(b) && (strncmp(a, b, strlen(a)) == 0) ? 1 : 0;
}

int main(int argc, char **argv) {
    int has_visited[WORD_LENGTH] = { 0 }, i, j;
    char buf[BUF_SIZE] = { 0 }, c;
    struct timeval start_time, end_time, result;

    /* initialise the random number generator and get our starting time */
    srand(time(NULL));
    assert(gettimeofday(&start_time, NULL) == 0);

    assert(printf("This is a game that tests typing speed Type the following words:\n") > -1);

    /* go through all the words */
    for (i = 0; i < WORD_LENGTH; ++i) {
        /* 
         * To get a unique word each time without duplicates, we use a boolean array, has_visited
         * to mark whether each index in the words array has already been used. We then generate
         * a random index in the words array, if the word has already been used then keep generating 
         * random indexes until an unused one is found.
        */
        int curr_word = rand() % WORD_LENGTH;
        while (has_visited[curr_word] == 1)
            curr_word = rand() % WORD_LENGTH;
        
        has_visited[curr_word] = 1;

        /* loop until the inputted strings match */
        while (!compare(buf, words[curr_word])) {
            assert(printf("word #%d is %s: ", i + 1, words[curr_word]) > -1);
            assert(scanf("%10s", buf) > 0);
            while((c = getchar()) != '\n' && c != EOF); /* consume unneeded chars */
        }

        for (j = 0; j < BUF_SIZE; ++j) // clear our input buffer
            buf[j] = '\0';
    }

    /* get ending time, get the total time, print results */
    assert(gettimeofday(&end_time, NULL) == 0);
    timersub(&end_time, &start_time, &result);
    assert(printf("You took %ld seconds and %06d microseconds\n", result.tv_sec, result.tv_usec) > -1);

    return 0;
}
