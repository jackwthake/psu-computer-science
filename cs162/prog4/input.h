#ifndef INPUT_H
#define INPUT_H

void get_input(const char *prompt, int &value);
void get_input_phrase(const char *prompt, char *value, int length);
void get_input_word(const char *prompt, char *value);

#endif