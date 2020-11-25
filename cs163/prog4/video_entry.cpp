/*
 * Jack Thake, CS163, Karla Fant
 * This file holds all implementations for the video_tree class
*/

#include "video_entry.h"
#include <cstring>
#include <iostream>
using namespace std;

/* create a blank video */
video_entry::video_entry() {
  this->class_name = this->media_name = this->desc = this->next = NULL;
  this->len = 0;
}


/* create a populated video */
video_entry::video_entry(char *class_name, char *media_name, char *desc, int len, char *next) {
  /* copy in each member */
  this->class_name = new char[strlen(class_name) + 1];
  strcpy(this->class_name, class_name);

  this->media_name = new char[strlen(media_name) + 1];
  strcpy(this->media_name, media_name);

  this->desc = new char[strlen(desc) + 1];
  strcpy(this->desc, desc);

  this->next = new char[strlen(next) + 1];
  strcpy(this->next, next);

  this->len = len;
}


/* deallocate all memory */
video_entry::~video_entry() {
  /* deallocate members if they exist */
  if (this->class_name)
    delete []this->class_name;

  if (this->media_name)
    delete []this->media_name;

  if (this->desc)
    delete []this->desc;

  if (this->next)
    delete []this->next;

  /* 0 things out */
  this->class_name = NULL;
  this->media_name = NULL;
  this->desc = NULL;
  this->next = NULL;
  this->len = 0;
}


/* print self */
int video_entry::print(void) const {
  if (!is_valid())
    return -1;

  cout << "Media Name: " << this->media_name << endl;
  cout << "Course Name: " << this->class_name << endl;
  cout << "Description: " << this->desc << endl;
  cout << "Length: " << this->len << " Minutes" << endl;
  cout << "Next Video: " << this->next << endl;

  return 1;
}


/* check if we are a valid object */
bool video_entry::is_valid(void) const {
  if (this->class_name)
    return true;

  return false; 
}


/* check if our course is the same as the passed string */
bool video_entry::is_same_course(const char *b) const { 
  return !strcmp(this->class_name, b);
}


/* overloaded assignment operator */
void video_entry::operator=(const video_entry &b) {
  /* deallocate old members */
  this->~video_entry();
  
  /* copy over members */
  if (b.class_name) {
    this->class_name = new char[strlen(b.class_name) + 1];
    strcpy(this->class_name, b.class_name);
  }

  if (b.media_name) {
    this->media_name = new char[strlen(b.media_name) + 1];
    strcpy(this->media_name, b.media_name);
  }

  if (b.desc) {
    this->desc = new char[strlen(b.desc) + 1];
    strcpy(this->desc, b.desc);
  }

  if (b.next) {
    this->next = new char[strlen(b.next) + 1];
    strcpy(this->next, b.next);
  }

  this->len = b.len;
}


/* overloaded equality operator */
bool video_entry::operator==(const video_entry &b) const {
  if (!this->is_valid() && !b.is_valid())
    return false;
  if (this->is_valid() && b.is_valid()) {
    if (strcmp(this->media_name, b.media_name) == 0)
      return true;
  }

  return false;
}


/* overloaded equality operator for strings */
bool video_entry::operator==(const char *b) const {
  if (strcmp(this->media_name, b) == 0)
    return true;

  return false;
}

/* overloaded less than operator */
bool video_entry::operator<(const video_entry &b) const {
  if (strcmp(this->media_name, b.media_name) < 0)
    return true;

  return false;
}


/* overloaded less than operator for strings */
bool video_entry::operator<(const char *b) const {
  if (strcmp(this->media_name, b) < 0)
    return true;

  return false;
}

