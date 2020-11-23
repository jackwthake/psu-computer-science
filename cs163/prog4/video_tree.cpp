#include "video_tree.h"
#include <cstddef>


video_tree::video_tree() {
  this->root = NULL;
}


int remove_all_recurs(node * &root) {
  if (!root)
    return 0;

  remove_all_recurs(root->left);
  remove_all_recurs(root->right);

  if (!root->left && !root->right) {
    delete root;
    root = NULL;
  }

  return 1;
}


video_tree::~video_tree() {
  remove_all_recurs(this->root);
}


int insert_recurs(node * &root, const video_entry &to_add) {
  if (!root) {
    root = new node;
    if (!root)
      return -1;

    root->data = to_add;
    root->left = root->right = NULL;

    return 1;
  }

  if (to_add < root->data) {
    return insert_recurs(root->left, to_add);
  } else {
    return insert_recurs(root->right, to_add);
  }
}


int video_tree::insert(const video_entry &to_add) {
  if (!this->root) {
    this->root = new node;
    if (!this->root)
      return -1;

    this->root->data = to_add;
    this->root->left = this->root->right = NULL;

    return 1;
  }

  return insert_recurs(this->root, to_add);
}


//int get_height_recurs(node *root);
//int video_tree::get_height(void) const;
