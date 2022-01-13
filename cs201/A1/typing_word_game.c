#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* contains all of the words that the program will ask the user to type */
#define WORD_LENGTH 9
static const char *words[WORD_LENGTH] = { "The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog" };

/* compare two strings appropriately */
int compare(const char *a, const char *b) {
    return strlen(a) == strlen(b) && (strncmp(a, b, strlen(a)) == 0) ? 1 : 0;
}

int main(int argc, char **argv) {
    int has_visited[WORD_LENGTH] = { 0 }, i;
    char buf[10] = { 0 }, c;
    struct timeval start_time, end_time, result;

    /* initialise the random number generator and get our starting time */
    srand(time(NULL));
    assert(gettimeofday(&start_time, NULL) == 0);

    printf("This is a game that tests typing speed Type the following words:\n");

    /* go through all the words */
    for (i = 0; i < WORD_LENGTH; ++i) {
        int curr_word = rand() % WORD_LENGTH;
        while (has_visited[curr_word] == 1) /* only use a word once */
            curr_word = rand() % WORD_LENGTH;
        
        has_visited[curr_word] = 1;

        /* loop until the inputted strings match */
        while (!compare(buf, words[curr_word])) {
            printf("word #%d is %s: ", i + 1, words[curr_word]);
            scanf("%10s", buf);
            while((c = getchar()) != '\n' && c != EOF); /* consume unneeded chars */
        }

        memset(buf, 0x00, 10);
    }

    /* get ending time, get the total time, print results */
    assert(gettimeofday(&end_time, NULL) == 0);
    timersub(&end_time, &start_time, &result);
    printf("You took %ld seconds and %06d microseconds\n", result.tv_sec, result.tv_usec);

    return 0;
}
