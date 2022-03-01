#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "menu.h"

/*
 * Little helper to print an error message and exit returning an error code
*/
void exit_error_state(const char *err) {
    fprintf(stderr, "%s\n", err);
    exit(EXIT_FAILURE);
}


/*
 * Checks if a buffer has the beggining of a hex string 
*/
int is_valid_hex(const char *arg) {
    if (*arg != '0' && tolower(arg[1]) != 'x') {
        return 0;
    }

    return 1;
}


/*
 * Process the command line arguments, populating the callback_args struct
*/
int process_args(callback_args *args, int argc, char **argv) {
    if (!args || !argv) {
        return 0;
    }

    /* 
     * NOTE: I'm not deep copying argv because to my knowledge there's no chance of it getting deallocated, 
     *       unless the program itself exits or aborts.
    */
    args->argc = argc;
    args->argv = argv;
    args->parsed = calloc(argc, sizeof(int));
    if (!args->parsed) {
        return 0;
    }

    /* parse and copy over arguments */
    int i = 0;
    char *fail_ptr = NULL;
    for (; i < argc; ++i) {
        if (is_valid_hex(argv[i])) { /* possible hex string */
            args->parsed[i] = strtol(argv[i], &fail_ptr, 16);

            if (strncmp(fail_ptr, "", 1) != 0) { /* check for invalid input */
                return 0;
            }
        } else { /* not a hex string */
            args->parsed[i] = strtol(argv[i], &fail_ptr, 10);

            if (strncmp(fail_ptr, "", 1) != 0) { /* check for invalid input */
                return 0;
            }
        }
    }

    return 1;
}


int main(int argc, char **argv) {
    callback_args args;
    if (argc < 3 || argc > 15) {
      exit_error_state("Invalid number of inputs supplied.");
    }

    if (!process_args(&args, argc - 1, argv + 1)) { /* we advance argv just to isolate the actual arguments */
        exit_error_state("Failed to parse arguments.");
    }

    return EXIT_SUCCESS;
}