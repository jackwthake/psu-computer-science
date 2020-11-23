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
    int get_height(void) const;
  private:

    node *root;

    friend int insert_recurs(node * &root, const video_entry &);
    friend int remove_all_recurs(node * &root);
    friend int get_height_recurs(node *root);
};

#endif
