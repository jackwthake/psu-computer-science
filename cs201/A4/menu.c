#include "menu.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MENU_TEXT_MAX_LENGTH 10

/*
 * Creates a memory entry structure, copying over relevant memory
*/
int create_entry(menu_entry_t *entry, const char *text, menu_callback callback) {
    if (!entry || !text) { /* can't populate a null pointer, can't deep copy a null pointer */
        return 0;
    }

    /* populate fields */
    entry->callback = callback;
    entry->menu_length = strnlen(text, MENU_TEXT_MAX_LENGTH);
    entry->menu_text = calloc(entry->menu_length, sizeof(char)); /* allocate and copy over text */
    if (!entry->menu_text || !strncpy(entry->menu_text, text, entry->menu_length)) {
        return 0;
    }

    return 1;
}

/*
 * Deallocates menu_entry's dynamically allocated text
*/
void destroy_entry(menu_entry_t *entry) {
    if (entry && entry->menu_text) {
        free(entry->menu_text);
    }
}

/*
 * Populate a menu structure with entries
*/
int create_menu(menu_t *menu, menu_entry_t *entries, size_t length) {
    if (!menu || !entries) { /* valid arguments check */
        return 0;
    }

    /* allocate menu entry array */
    menu->length = length;
    menu->entries = calloc(menu->length, sizeof(menu_entry_t));
    if (!menu->entries) {
        return 0;
    }

    /* populate array */
    int i = 0;
    for (; i < menu->length; ++i) {
        if (!create_entry(&menu->entries[i], entries[i].menu_text, entries[i].callback)) {
            return 0;
        }
    }

    return 1;
}


/*
 * Deallocate menu's entry array
*/
void destroy_menu(menu_t *menu) {
    if (menu && menu->entries) {
        int i = 0;
        for(; i < menu->length; ++i) {
            destroy_entry(&menu->entries[i]); /* first destroy entries */
        }

        free(menu->entries); /* then we can deallocate the array */
    }
}

/*
 * Print out the menu entries, per spec.
*/
void print_menu(menu_t *menu) {
    int i = 0;
    for (; i < menu->length; ++i) {
        printf("%d.\t%s\n", i, menu->entries[i].menu_text);
    }
}

/*
 * Execute an entry's function pointer at a given index
*/
void execute_entry(menu_t *menu, unsigned index, callback_args *args) {
    if (index < menu->length) { /* bounds check */
        menu->entries[index].callback(args);
    } else {
        printf("Invalid index.\n");
    }
}
