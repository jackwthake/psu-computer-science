#include "menu.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MENU_TEXT_MAX_LENGTH 10

int create_entry(menu_entry_t *entry, const char *text, menu_callback callback) {
    if (!entry || !text) {
        return 0;
    }

    entry->callback = callback;
    entry->menu_length = strnlen(text, MENU_TEXT_MAX_LENGTH);
    entry->menu_text = calloc(entry->menu_length, sizeof(char));
    if (!entry->menu_text || !strncpy(entry->menu_text, text, entry->menu_length)) {
        return 0;
    }

    return 1;
}

void destroy_entry(menu_entry_t *entry) {
    if (entry && entry->menu_text) {
        free(entry->menu_text);
    }
}



int create_menu(menu_t *menu, menu_entry_t *entries, size_t length) {
    if (!menu || !entries) {
        return 0;
    }

    menu->length = length;
    menu->entries = calloc(menu->length, sizeof(menu_entry_t));
    if (!menu->entries) {
        return 0;
    }

    int i = 0;
    for (; i < menu->length; ++i) {
        if (!create_entry(&menu->entries[i], entries[i].menu_text, entries[i].callback)) {
            return 0;
        }
    }

    return 1;
}

void destroy_menu(menu_t *menu) {
    if (menu && menu->entries) {
        int i = 0;
        for(; i < menu->length; ++i) {
            destroy_entry(&menu->entries[i]);
        }

        free(menu->entries);
    }
}

void print_menu(menu_t *menu) {
    int i = 0;
    for (; i < menu->length; ++i) {
        printf("%d.\t%s\n", i, menu->entries[i].menu_text);
    }
}


void execute_entry(menu_t *menu, unsigned index, callback_args *args) {
    if (index < menu->length) {
        menu->entries[index].callback(args);
    } else {
        printf("Invalid index.\n");
    }
}