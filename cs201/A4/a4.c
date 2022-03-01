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
int is_hex(const char *arg) {
    if (*arg == '-') { /* consume negative sign */
        ++arg;
    }

    if (*arg != '0' && tolower(arg[1]) != 'x') {
        return 0;
    }

    return 1;
}

void print_nums_format(int *args, size_t length, int result, int is_hex, const char *seporator) {
    int i = 1;
    if (is_hex) {
        printf("0x%x", args[0]);
    } else {
        printf("%d", args[0]);
    }

    for (; i < length; ++i) {
        if (is_hex) {
            printf(" %s 0x%x", seporator, args[i]);
        } else {
            printf(" %s %d", seporator, args[i]);
        }
    }

    if (is_hex) {
        printf(" = 0x%x\n", result);
    } else {
        printf(" = %d\n", result);
    }
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
        if (is_hex(argv[i])) { /* possible hex string */
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


/*
 * Menu callback functions
*/

void exit_com(callback_args *args) {
    exit(EXIT_SUCCESS);
}

void addition_com(callback_args *args) {
    int i = 0, acc = 0;
    for (; i < args->argc; ++i) {
        acc += args->parsed[i];
    }

    print_nums_format(args->parsed, args->argc, acc, 0, "+");
    print_nums_format(args->parsed, args->argc, acc, 1, "+");
}

void subtraction_com(callback_args *args) {
    int i = 1, acc = args->parsed[0];
    for (; i < args->argc; ++i) {
        acc -= args->parsed[i];
    }

    print_nums_format(args->parsed, args->argc, acc, 0, "-");
    print_nums_format(args->parsed, args->argc, acc, 1, "-");
}

void multiplication_com(callback_args *args) {
    int i = 1, acc = args->parsed[0];
    for (; i < args->argc; ++i) {
        acc *= args->parsed[i];
    }

    print_nums_format(args->parsed, args->argc, acc, 0, "*");
    print_nums_format(args->parsed, args->argc, acc, 1, "*");
}

void division_com(callback_args *args) {
    float res = args->parsed[0] / args->parsed[1];
    printf("%d / %d = %f\n", args->parsed[0], args->parsed[1], res);
}

void modulo_com(callback_args *args) {
    int res = args->parsed[0] % args->parsed[1];

    print_nums_format(args->parsed, 2, res, 0, "mod");
    print_nums_format(args->parsed, 2, res, 1, "mod");
}

void reverse_com(callback_args *args) {
    int i = args->argc - 1;
    for (; i >= 0; --i) {
        char *str = args->argv[i];
        int j = strnlen(str, 10); //TODO: Find currect max length of number
        for (; j >= 0; --j) {
            putc(str[j], stdout);
        }

        putc(' ', stdout);
    }
}


/*
 * Register all menu functions
*/
int create_and_register_entries(menu_t *menu) {
    if (!menu) {
        return 0;
    }

    menu_entry_t entries[7] = { 
        { 5, "Exit", exit_com },
        { 9, "Addition", addition_com },
        { 12, "Subtraction", subtraction_com },
        { 15, "Multiplication", multiplication_com },
        { 9, "Division", division_com },
        { 7, "Modulo", modulo_com },
        { 14, "Reverse Input", reverse_com }
    };
    
    if (!create_menu(menu, entries, 7)) {
        return 0;
    }

    return 1;
}


int main(int argc, char **argv) {
    callback_args args;
    menu_t main_menu;

    if (argc < 3 || argc > 16) {
      exit_error_state("Invalid number of inputs supplied.");
    }

    if (!process_args(&args, argc - 1, argv + 1)) { /* we advance argv just to isolate the actual arguments */
        exit_error_state("Failed to parse arguments.");
    }

    if (!create_and_register_entries(&main_menu)) {
        exit_error_state("Failed to register menu entries.");
    }

    for (;;) {
        int choice = 0;
        
        printf("\n");
        print_menu(&main_menu);
        printf("\nMenu item: ");
        scanf("%1d", &choice);
        execute_entry(&main_menu, choice, &args);
    }

    return EXIT_SUCCESS;
}