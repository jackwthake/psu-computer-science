#include "menu.h"

#include <stdlib.h>
#include <string.h>

#define MENU_TEXT_MAX_LENGTH 10

int create_entry(menu_entry_t *entry, const char *text, menu_callback callback) {
    size_t length = strnlen(text, MENU_TEXT_MAX_LENGTH);
    
    entry->menu_text = calloc(length, sizeof(char));
    if (!entry->menu_text || !strncpy(entry->menu_text, text, length)) {
        return 0;
    }

    entry->menu_text[length - 1] = '\0'; /* ensure string is terminated */
    entry->callback = callback;

    return 1;
}

void destroy_entry(menu_entry_t *entry) {
    if (entry->menu_text) {
        free(entry->menu_text);
    }
}