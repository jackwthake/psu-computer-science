#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* contains all of the words that the program will ask the user to type */
#define WORD_LENGTH 9
static const char *words[WORD_LENGTH] = { "The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog" };

int main(int argc, char **argv) {
    int has_visited[WORD_LENGTH] = { 0 }, i;        /* this array will be used as a boolean array for whether a word has already been typed */
    char buf[10] = { 0 };
    struct timeval start_time, end_time;            /* these will be used to measure the time the user takes */

    srand(time(NULL));                              /* initialise the random number generator */
    assert(gettimeofday(&start_time, NULL) == 0);   /* get the starting time for the timer */

    for (i = 0; i < WORD_LENGTH; ++i) {
        char c;
        int curr_word = rand() % WORD_LENGTH;       /* get a random index in the words array */
        while (has_visited[curr_word] == 1)         /* keep generating new indexes until an unused one is found */
            curr_word = rand() % WORD_LENGTH;
        
        has_visited[curr_word] = 1;                 /* set the unused word to used for the next iteration */

        /* loop until the inputted strings match */
        while (strncmp(buf, words[curr_word], strlen(words[curr_word])) != 0) {
            printf("%s: ", words[curr_word]);       /* print out the word to type, and except the appropriately sized input */
            scanf("%10s", buf);
            while((c = getchar()) != '\n' && c != EOF); /* consume unused characters */
        }

        memset(buf, 0x00, 10);                      /* without this, we could get with a different set of words false match */
    }

    assert(gettimeofday(&end_time, NULL) == 0);     /* get the ending time for the timer */
    printf("Total time taken: %ld.%06d seconds\n", end_time.tv_sec - start_time.tv_sec, end_time.tv_usec - start_time.tv_usec);

    return 0;
}
