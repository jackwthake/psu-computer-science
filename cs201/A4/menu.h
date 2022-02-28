#ifndef __MENU_H__
#define __MENU_H__

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

#endif