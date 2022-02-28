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
    menu_entry_t entries[1];
    create_entry(&entries[0], "hellow", test_callback);

    menu_t menu;
    create_menu(&menu, entries, 1);

    if (argc < 3 || argc > 15) {
      exit_error_state("Invalid number of inputs supplied.");
    }

    print_menu(&menu);
    execute_entry(&menu, 0, NULL);

    destroy_menu(&menu);
    destroy_entry(&entries[0]);
    return EXIT_SUCCESS;
}