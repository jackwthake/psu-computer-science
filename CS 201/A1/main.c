#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define UNUSED(x) (void)(x)

/* contains all of the words that the program will ask the user to type */
#define WORD_LENGTH 9
static const char *words[WORD_LENGTH] = { "The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog" };

int main(int argc, char **argv) {
    int has_visited[WORD_LENGTH] = { 0 }, i;

    UNUSED(argc);
    UNUSED(argv);
    srand(time(NULL));

    for (i = 0; i < 9; ++i) {
        int word = rand() % WORD_LENGTH;
        while (has_visited[word] == 1)
            word = rand() % WORD_LENGTH;
        
        has_visited[word] = 1;
        
        printf("%s\n", words[word]);
    }

    return 0;
}
