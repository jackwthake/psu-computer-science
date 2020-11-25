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


static int search_recurs(node *root, const char *key, video_entry * &res, int &length) {
  bool is_match = false;
  int idx = 0;

  /* empty node */
  if (!root) return 0;

  /* check for matching data */
  if (root->data == key) {
    ++length;
    is_match = true;
  }

  /* if we're a child create array and start unraveling stack frames */
  if (!root->left && !root->right) {
    res = new video_entry[length];
    res[0] = root->data;

    return 1;
  }


  /* still traversal left to do */
  if (root->data < key) /* move left */
    idx += search_recurs(root->left, key, res, length);
  else /* move right */
    idx += search_recurs(root->right, key, res, length);

  /* add ourselves to the result array if we match */
  if (is_match) {
    res[idx] = root->data;
    return ++idx;
  }

  return idx;
}


static void get_ios_and_delete_recurs(node * &root, video_entry &res) {
  if (!root)
    return;
  else if (!root->left) {
    res = root->data;

    node *tmp = root->right;
    delete root;
    root = tmp;

    return;
  }

  return get_ios_and_delete_recurs(root->left, res);
}


static int remove_media_recurs(node * &root, const char *key) {
  int count = 0;

  if (!root)
    return 0;

  if (root->data == key) {
    ++count;

    if (!root->left && !root->right) { /* node is a leaf */
      delete root;
      root = NULL; 

      return count;
    } 
    
    if ((root->left || root->right) && !(root->left && root->right)) { /* node only has one child */
      if (root->left) {
        node *tmp = root->left;
        delete root;
        root = tmp;
      } else {
        node *tmp = root->right;
        delete root;
        root = tmp;
      }
    } else { /* node has two children */
      video_entry ios;
      get_ios_and_delete_recurs(root->right, ios);
      root->data = ios;
    }
  }

  /* still traversal left to do */
  if (root->data < key) /* move left */
    count += remove_media_recurs(root->right, key);
  else /* move right */
    count += remove_media_recurs(root->left, key);

  return count;
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


int video_tree::search(const char *key, video_entry * &res, int &length) {
  if (!this->root && !key)
    return -1;

  return search_recurs(this->root, key, res, length);
}


int video_tree::remove(const char *key) {
  if (!this->root)
    return -1;

  return remove_media_recurs(this->root, key);
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

