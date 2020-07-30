#ifndef COMMANDS_H
#define COMMANDS_H

#include "list.h"

enum {
  cmd_type_create,
  cmd_type_search,
  cmd_type_display,
  cmd_type_quit,
  cmd_type_help,
  cmd_type_unknown
};

const unsigned cmd_size = 10;

/* input functions */
void get_input(const char *prompt, char *res, int len);
void get_input_value(const char *prompt, int &value);
void get_input_value(const char *prompt, float &value);

/* command functions  */
int get_user_command();
void create_command(list &data);
void search_command(list &data);
void display_command(list &data);
void help_command();

#endif
