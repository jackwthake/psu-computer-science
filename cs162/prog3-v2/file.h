/*
 * Jack Thake, Program 3, Aug 3 2020, CS162
 *
 * This file holds all prototypes for interecting with a data file.
*/

#ifndef LIST_H
#define LIST_H

#include "pizza.h"

void read_file(const char *fp, pizza list[], int length);
bool write_file(const char *fp, pizza list[], int length);

#endif
