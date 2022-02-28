#include <stdlib.h>
#include <stdio.h>

#include "menu.h"

void exit_error_state(const char *err) {
    printf("%s\n", err);
    exit(EXIT_FAILURE);
}

void test_callback(callback_args *args) {
    printf("Hellowabccc\n");
}

int main(int argc, char **argv) {
    menu_entry_t entry;
    if (!create_entry(&entry, "hello", test_callback)) {
        exit_error_state("Failed to create entry");
    }

    if (argc < 3 || argc > 15) {
       exit_error_state("Invalid number of inputs supplied.");
    }

<<<<<<< HEAD
    printf("%s\n", entry.menu_text);
    entry.callback(NULL);
    destroy_entry(&entry);
=======
    menu_entry_t *entry = create_menu_entry("hello", NULL);
    if (!entry) {
        printf("failed to create entry\n");
    } else {
        printf("%s\n", entry->text);
    }
    destroy_menu_entry(entry);
>>>>>>> 14be8afd56acf661bd98bf390e6438af4fc3332c

    return EXIT_SUCCESS;
}