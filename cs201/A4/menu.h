#ifndef __MENU_H__
#define __MENU_H__

<<<<<<< HEAD
#include <stddef.h>

/*
 * Helper struct to group together arguments
*/
typedef struct callback_args {
    size_t argc, length;
    char *argv;
    int *parsed;
} callback_args;

/* callback function for menu entries */
typedef void (*menu_callback)(callback_args *);

/*
 * Represents one entry in the menu
*/
typedef struct menu_entry_t {
    int valid;
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
=======
typedef struct menu_entry_t {
    char *text;
    void (*menu_func)(int *);
} menu_entry_t;

typedef struct menu_t {
    menu_entry_t *entries;
    size_t length;
} menu_t;


menu_entry_t *create_menu_entry(const char *text, void (*menu_func)(int *));
void destroy_menu_entry(menu_entry_t *);
>>>>>>> 14be8afd56acf661bd98bf390e6438af4fc3332c

#endif