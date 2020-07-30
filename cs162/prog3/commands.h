#ifndef COMMANDS_H
#define COMMANDS_H

#include "list.h"

enum command_type {
  command_create,
  command_search,
  command_display,
  command_quit,
  command_help,
  command_unknown
};

const unsigned cmd_size = 10;

/* input functions */
void get_input(const char *prompt, char *res, int len);
void get_input_value(const char *prompt, int &value);
void get_input_value(const char *prompt, float &value);

/* command functions  */
command_type get_user_command();
void create_command(list &data);
void search_command(list &data);
void display_command(list &data);
void help_command();

#endif
