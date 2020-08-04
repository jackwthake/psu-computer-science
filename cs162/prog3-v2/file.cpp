/*
 * Jack Thake, Program 3, Aug 3 2020, CS162
 *
 * This file holds all functionality for interecting with a data file.
*/

#include "file.h"

#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;


/* 
 * reads in a portion of the passed file, static because it is not needed in
 * global scope.
*/
static void read_from_file(ifstream &file, char response[], int length) {
  file.get(response, length, '|'); /* read in description member */
  file.ignore(100, '|');
}


/*
 * reads in a data file, filling out the passed array with pizza structs,
 * returns true the file was successfully opened and read from, false otherwise.
*/
bool read_file(const char *fp, pizza list[], int length) {
  int index = 0;
  char temp[field_length];

  ifstream data;
  data.open(fp);

  if(!data)
    return false;

  while(!data.eof() && index < length) {
    read_from_file(data, list[index].name, field_length);
    read_from_file(data, list[index].description, field_length);
    read_from_file(data, list[index].additions, field_length);
    read_from_file(data, list[index].removals, field_length);
    read_from_file(data, list[index].price, price_length);

    data >> list[index].rating;
    data.ignore(100, '\n');

    ++index;
  }

  data.close();
  return true;
} 


/*
 * writes the passed array to the specified data file. returns true if the files
 * was successfully opened and written to, false otherwise.
*/
bool write_file(const char *fp, pizza list[], int length) {
  ofstream data;
  data.open(fp);

  if(!data)
    return false;
  
  for(int i = 0; i < length; ++i) {
    if(strcmp(list[i].name, "") != 0) {
      data << list[i].name << "|"
           << list[i].description << "|"
           << list[i].additions << "|"
           << list[i].removals << "|"
           << list[i].price << "|"
           << list[i].rating << "\n";
    }
  }

  data.close();
  return true;
}
