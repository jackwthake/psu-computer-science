#include "menu.h"

#include <stdlib.h>
#include <string.h>

<<<<<<< HEAD
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
=======
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
>>>>>>> 14be8afd56acf661bd98bf390e6438af4fc3332c
    }
}