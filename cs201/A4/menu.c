#include "menu.h"

#include <stdlib.h>
#include <string.h>

menu_entry_t *create_menu_entry(const char *text, void (*menu_func)(int *)) {
    size_t text_len = strnlen(text, 10);
    menu_entry_t *entry = calloc(1, sizeof(menu_entry_t));
    if (!entry) {
        return NULL;
    }

    entry->text = calloc(text_len, sizeof(char));
    if (!entry->text || !strncpy(entry->text, text, text_len)) {
        destroy_menu_entry(entry);
        return NULL;
    }
    
    entry->menu_func = menu_func;
    return entry;
}

void destroy_menu_entry(menu_entry_t *entry) {
    if (entry) {
        free(entry->text);
        free(entry);
    }
}