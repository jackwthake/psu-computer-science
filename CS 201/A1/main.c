#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* contains all of the words that the program will ask the user to type */
#define WORD_LENGTH 9
static const char *words[WORD_LENGTH] = { "The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog" };

int main(int argc, char **argv) {
    int has_visited[WORD_LENGTH] = { 0 }, i;
    char buf[10] = { 0 }, c;
    struct timeval start_time, end_time;

    srand(time(NULL));
    assert(gettimeofday(&start_time, NULL) == 0);

    for (i = 0; i < WORD_LENGTH; ++i) {
        int curr_word = rand() % WORD_LENGTH;
        while (has_visited[curr_word] == 1)
            curr_word = rand() % WORD_LENGTH;
        
        has_visited[curr_word] = 1;

        while (strncmp(buf, words[curr_word], strlen(words[curr_word])) != 0) {
            printf("%s: ", words[curr_word]);
            scanf("%10s", buf);
            while((c = getchar()) != '\n' && c != EOF);
        }

        memset(buf, 0x00, 10);
    }

    assert(gettimeofday(&end_time, NULL) == 0);
    end_time.tv_sec -= start_time.tv_sec;
    end_time.tv_usec -= start_time.tv_usec;

    printf("Total time taken: %ld.%06d seconds\n", end_time.tv_sec, end_time.tv_usec);

    return 0;
}
