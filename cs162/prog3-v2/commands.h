#ifndef COMMANDS_H
#define COMMANDS_H

#include "pizza.h"

enum {
  cmd_create = 0,
  cmd_search,
  cmd_display,
  cmd_help,
  cmd_quit,
  cmd_unknown
};

const int cmd_size = 50;

int get_user_command(void);
void createCommand(pizza list[], int length);
void searchCommand(pizza list[], int length);
void displayCommand(pizza list[], int length);
void helpCommand();

#endif

 
