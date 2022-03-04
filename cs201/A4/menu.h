#ifndef __MENU_H__
#define __MENU_H__

#include <stddef.h>

/*
 * strnlen seems to be a wonky function in the standard, every resource I've looked at
 * claims it should be in string.h (including man pages). However, there doesn't seem
 * to be a proptotype in there. This supresses compiler warnings
*/
extern size_t strnlen(const char *, size_t);

/*
 * Helper struct to group together arguments
*/
typedef struct callback_args {
    size_t argc, parsed_len;
    char **argv;
    int *parsed;
} callback_args;

/* callback function for menu entries */
typedef void (*menu_callback)(callback_args *);

/*
 * Represents one entry in the menu
*/
typedef struct menu_entry_t {
    size_t menu_length;
    char *menu_text;
    menu_callback callback;
} menu_entry_t;


/*
 * Main menu manager
*/
typedef struct menu_t {
    size_t length;
    menu_entry_t *entries;
} menu_t;


/* menu_entry_t functions */
int create_entry(menu_entry_t *entry, const char *text, menu_callback callback);
void destroy_entry(menu_entry_t *entry);

/* menu_t functions */
int create_menu(menu_t *menu, menu_entry_t *entries, size_t length);
void destroy_menu(menu_t *menu);
void print_menu(menu_t *menu);
void execute_entry(menu_t *menu, unsigned index, callback_args *args);

#endif