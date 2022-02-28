#include <stdlib.h>
#include <stdio.h>

#include "menu.h"

void exit_error_state(const char *err) {
    printf("%s\n", err);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    if (argc < 3 || argc > 15) {
        exit_error_state("Invalid number of inputs supplied.");
    }

    return EXIT_SUCCESS;
}