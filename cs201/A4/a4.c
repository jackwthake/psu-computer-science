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

    menu_entry_t *entry = create_menu_entry("hello", NULL);
    if (!entry) {
        printf("failed to create entry\n");
    } else {
        printf("%s\n", entry->text);
    }
    destroy_menu_entry(entry);

    return EXIT_SUCCESS;
}