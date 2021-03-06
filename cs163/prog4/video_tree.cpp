/*
 * Jack Thake, CS163, Karla Fant
 * This file holds all implementations for video_tree class and it's static 
 * recursive functions.
*/

#include "video_tree.h"
#include <cstddef>
#include <iostream>

using namespace std;

//
/// Static recursive functions here - 
//

/* deallocate entire tree */
static int remove_all_recurs(node * &root) {
  if (!root) /* base case */
    return 0;

  /* get to the leaves first */
  remove_all_recurs(root->left);
  remove_all_recurs(root->right);

  /* if we are a leaf */
  if (!root->left && !root->right) {
    delete root;
    root = NULL;
  }

  /* success */
  return 1;
}


/* insert to the tree in the appropriate position */
static int insert_recurs(node * &root, const video_entry &to_add) {
  if (!root) { /* found the insertion point */
    root = new node;
    if (!root)
      return -1;

    /* bring in data */
    root->data = to_add;
    root->left = root->right = NULL;

    /* success */
    return 1;
  }

  /* keep going through the tree */
  if (to_add < root->data) {
    return insert_recurs(root->left, to_add);
  } else {
    return insert_recurs(root->right, to_add);
  }
}


/* search through tree populating array with matches */
static int search_recurs(node *root, const char *key, video_entry * &res, int &length) {
  int idx = 0; /* used to keep track of the current index */
  bool is_match = false; /* used for tracking if a node has matched */

  if (!root) { return 0; } /* empty node */
  else if (root->data.is_valid()) { /* only compare if node is valid */
    if (root->data == key) { /* compare using overloaded operator */
      is_match = true; 
      ++length; /* increase array length */
    }
  }

  /* if we're at a leaf, we know how long our result list is */
  if (!root->left && !root->right) {
    if (length > 0) { /* only allocate if items were found */
      res = new video_entry[length];
    }
  }

  /* move to next node */
  /* if the root's data is less than the key (key is greator than or equal to root's data), go right. */
  if (root->data < key) { /* using overloaded operator to compare strings */
    idx += search_recurs(root->right, key, res, length); /* next recursive call, update index. */
  } else { /* if the root's data is greator than the key (key is less than root's data), go left. */
    idx += search_recurs(root->left, key, res, length); /* next recursive call, update index. */
  }

  /* now the stack is unwinding, check if this recursive call was a match */
  if (is_match && res) {
    res[idx] = root->data; /* add to results */
    ++idx; /* increment index for previous stack frame */
  }

  return idx;
}


/* grab the ios, store it's data and delete it */
static void get_ios_and_delete_recurs(node * &root, video_entry &res) {
  if (!root) /* no node */
    return;
  else if (!root->left) { /* found ios */
    res = root->data; /* copy data */

    /* delete node, set it's parent to adopt right pointer if right exists */
    node *tmp = root->right;
    delete root;
    root = tmp;

    /* unravel stack */
    return;
  }

  /* keep going down the tree */
  return get_ios_and_delete_recurs(root->left, res);
}


/* remove all nodes of the matching media name */
static int remove_media_recurs(node * &root, const char *key) {
  int count = 0;

  if (!root)
    return 0;

  if (root->data == key) { /* found a matching node */
    ++count; /* increment count */

    if (!root->left && !root->right) { /* node is a leaf */
      delete root;
      root = NULL; 

      /* since we're a leave theres nothing more to traverse */
      return count;
    } 
    
    if ((root->left || root->right) && !(root->left && root->right)) { /* node only has one child */
      node *tmp;
      if (root->left)
        tmp = root->left;
      else
        tmp = root->right;

      delete root;
      root = tmp;
    } else { /* node has two children */
      /* find ios */
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


/* remove all nodes matching a specific course */
static int remove_course_recurs(node * &root, const char *key) {
  if (!root) /* no node to check */
    return 0;

  /* post order */
  int count = remove_course_recurs(root->left, key);
  count += remove_course_recurs(root->right, key);

  /* if root has a matching course */
  if (root->data.is_same_course(key)) {
    ++count;

    /* if root is a leaf */
    if (!root->left && !root->right) {
      delete root;
      root = NULL;
    } else if ((root->left || root->right) && !(root->left && root->right)) { /* if root has one child */
      node *tmp;
      if (root->left)
        tmp = root->left;
      else
        tmp = root->right;

      delete root;
      root = tmp;
    } else { /* if root has two children */
      video_entry ios;
      get_ios_and_delete_recurs(root->right, ios);
      root->data = ios;
    }
  }

  return count;
}


/* display all of tree recursively */
static int display_all_recurs(node *root) {
  if (!root)
    return 0;

  /* first look left */
  int ret = display_all_recurs(root->left);

  /* then print ourselves */
  cout << endl;
  root->data.print();
  ++ret;

  /* then look right */
  ret += display_all_recurs(root->right);

  return ret;
}


/* display all of a matching course */
static int display_course_recurs(node *root, const char *course) {
  if (!root)
    return 0;

  /* look left */
  int ret = display_course_recurs(root->left, course);

  /* handle our node */
  if (root->data.is_same_course(course)) {
    cout << endl;
    root->data.print();
    ++ret;
  }

  /* look right */
  return ret + display_course_recurs(root->right, course);
}


/* get tree height */
static int get_height_recurs(node *root) {
  if (!root) /* no node to count */
    return 0;
  if (!root->left && !root->right) /* got to a leaf */
    return 1;

  /* get distances down the tree */
  int left_dist = 1 + get_height_recurs(root->left);
  int right_dist = 1 + get_height_recurs(root->right);

  /* compare distances, returning larger one */
  if (right_dist >= left_dist)
    return right_dist;

  return left_dist;

}


//
/// video_tree member functions here -
//


/* set up tree */
video_tree::video_tree() {
  this->root = NULL;
}


/* deallocate */
video_tree::~video_tree() {
  remove_all_recurs(this->root);
}


/* insert into the list */
int video_tree::insert(const video_entry &to_add) {
  if (!this->root) { /* emoty tree */
    this->root = new node;
    if (!this->root)
      return -1;

    this->root->data = to_add;
    this->root->left = this->root->right = NULL;

    return 1;
  }

  /* insert into non empty tree */
  return insert_recurs(this->root, to_add);
}


/* search through tree */
int video_tree::search(const char *key, video_entry * &res, int &length) {
  if (!this->root || !key) /* dont try to dereference any NULL pointers */
    return -1;

  /* search through tree */
  return search_recurs(this->root, key, res, length);
}


/* remove from tree */
int video_tree::remove(const char *key) {
  if (!this->root)
    return -1;

  return remove_media_recurs(this->root, key);
}


/* remove all matching a specific course */
int video_tree::remove_course(const char *key) {
  if (!this->root)
    return -1;

  return remove_course_recurs(this->root, key);
}

/* display tree */
int video_tree::display_all(void) const {
  if (!this->root)
    return -1;

  return display_all_recurs(this->root);
}


/* display with course */
int video_tree::display_course(const char *course) const {
  if (!this->root)
    return -1;

  return display_course_recurs(this->root, course);
}


/* get the height of the tree */
int video_tree::get_height(void) const {
  return get_height_recurs(this->root);
}

