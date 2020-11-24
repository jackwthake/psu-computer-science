#include "video_tree.h"
#include <cstddef>
#include <iostream>

using namespace std;

//
/// Static recursive functions here - 
//

static int remove_all_recurs(node * &root) {
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


static int insert_recurs(node * &root, const video_entry &to_add) {
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


static int display_all_recurs(node *root) {
  if (!root)
    return 0;

  int ret = display_all_recurs(root->left);

  cout << endl;
  root->data.print();
  ++ret;

  ret += display_all_recurs(root->right);

  return ret;
}


static int display_course_recurs(node *root, const char *course) {
  if (!root)
    return 0;

  int ret = display_course_recurs(root->left, course);

  if (root->data.is_same_course(course)) {
    cout << endl;
    root->data.print();
    ++ret;
  }

  return ret + display_course_recurs(root->right, course);
}


static int get_height_recurs(node *root) {
  if (!root)
    return 0;
  if (!root->left && !root->right)
    return 1;

  int left_dist = 1 + get_height_recurs(root->left);
  int right_dist = 1 + get_height_recurs(root->right);

  if (right_dist  >= left_dist)
    return right_dist;

  return left_dist;

}


//
/// video_tree member functions here -
//

video_tree::video_tree() {
  this->root = NULL;
}


video_tree::~video_tree() {
  remove_all_recurs(this->root);
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


int video_tree::display_all(void) const {
  if (!this->root)
    return -1;

  return display_all_recurs(this->root);
}


int video_tree::display_course(const char *course) const {
  if (!this->root)
    return -1;

  return display_course_recurs(this->root, course);
}


int video_tree::get_height(void) const {
  return get_height_recurs(this->root);
}

