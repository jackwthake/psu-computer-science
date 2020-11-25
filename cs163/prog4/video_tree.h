/*
 * Jack Thake, CS163, Karla Fant
 * This file holds all declarations for the video_tree class
*/

#ifndef VIDEO_TREE_H
#define VIDEO_TREE_H

#include "video_entry.h"
  
/* one node in tree */
struct node {
  video_entry data;
  node *left, *right;
};

/* one tree */
class video_tree {
  public:
    video_tree(); /* constructor */
    ~video_tree(); /* deconstructor */

    int insert(const video_entry &); /* insert to tree */
    int search(const char *, video_entry *&, int &); /* video lookup */
    int remove(const char *); /* remove matching media name's */

    int display_all(void) const; /* display everything */
    int display_course(const char *) const; /* display all with in a course */
    int get_height(void) const; /* get tree height */
  private:
    node *root;
};

#endif
