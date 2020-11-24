#ifndef VIDEO_TREE_H
#define VIDEO_TREE_H

#include "video_entry.h"
  
struct node {
  video_entry data;
  node *left, *right;
};

class video_tree {
  public:
    video_tree();
    ~video_tree();

    int insert(const video_entry &);
    int search(const char *, video_tree *, int &);

    int display_all(void) const;
    int display_course(const char *) const;
    int get_height(void) const;
  private:
    node *root;
};

#endif
