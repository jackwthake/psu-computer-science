#include "video_entry.h"
#include <cstring>
#include <iostream>
using namespace std;

video_entry::video_entry() {
  this->class_name = this->media_name = this->desc = this->next = NULL;
}


video_entry::video_entry(char *class_name, char *media_name, char *desc, int len, char *next) {
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


video_entry::~video_entry() {
  if (this->class_name)
    delete []this->class_name;

  if (this->media_name)
    delete []this->media_name;

  if (this->desc)
    delete []this->desc;

  if (this->next)
    delete []this->next;

  this->class_name = NULL;
  this->media_name = NULL;
  this->desc = NULL;
  this->next = NULL;
  this->len = 0;
}


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


void video_entry::operator=(const video_entry &b) {
  this->~video_entry();
  
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


bool video_entry::operator==(const video_entry &b) {
  if (!this->is_valid() && !b.is_valid())
    return false;
  if (this->is_valid() && b.is_valid()) {
    if (strcmp(this->media_name, b.media_name) == 0)
      return true;
  }

  return false;
}

