/*
 * Jack Thake
 * Karla Fant
 * CS 202
 *
 * This file contains the definition to the binary search tree. this tree uses templates to make a generic
 * tree that can be used with all of the derived events.
*/

#include "bst.h"

#include <iostream>

/* constructors */
/* default */
template <class TYPE>
node<TYPE>::node() {
  this->left = this->right = NULL;
}


/* normal */
template <class TYPE>
node<TYPE>::node(TYPE &data) {
  this->data = data;
  this->left = this->right = NULL;
}


/* get left node */
template <class TYPE>
node<TYPE> * &node<TYPE>::get_left() {
  return this->left;
}


/* get right node */
template <class TYPE>
node<TYPE> * &node<TYPE>::get_right() {
  return this->right;
}


/* set left node */
template <class TYPE>
void node<TYPE>::set_left(node<TYPE> *left) {
  this->left = left;
}


/* set right node */
template <class TYPE>
void node<TYPE>::set_right(node<TYPE> *right) {
  this->right = right;
}


/* get a reference to the data */
template <class TYPE>
TYPE &node<TYPE>::get_data() {
  return this->data;
}


template <class TYPE>
void node<TYPE>::set_data(TYPE &data) {
  this->data = data;
}


/* Binary search tree template implementation */

/* default constructor */
template <class TYPE, typename attribute>
binary_search_tree<TYPE, attribute>::binary_search_tree() {
  this->root = NULL;
}


/* copy constructor */
template <class TYPE, typename attribute>
binary_search_tree<TYPE, attribute>::binary_search_tree(const binary_search_tree &to_copy) {
  this->copy_tree(this->root, to_copy.root); 
}


/* destructor */
template <class TYPE, typename attribute>
binary_search_tree<TYPE, attribute>::~binary_search_tree() {
  this->clear_tree(this->root);
}


/* wrapper function to recursively insert into the tree */
template <class TYPE, typename attribute>
bool binary_search_tree<TYPE, attribute>::insert(TYPE &to_add) {
  return this->insert(this->root, to_add);
}


/* search for by a key, populating a list with matches */
template <class TYPE, typename attribute>
void binary_search_tree<TYPE, attribute>::search(attribute &key, std::list<TYPE> &target) {
  this->search(this->root, key, target);
}


/* remove all matches */
template <class TYPE, typename attribute>
bool binary_search_tree<TYPE, attribute>::remove(attribute &key) {
  return this->remove(this->root, key);
}


/* Wrapper function to display the tree */
template <class TYPE, typename attribute>
void binary_search_tree<TYPE, attribute>::display_all() {
  this->display(this->root);
}


/* Wrapper function for getting the height */
template <class TYPE, typename attribute>
int binary_search_tree<TYPE, attribute>::get_height() {
  return this->get_height(this->root);
}

/* Overloaded operators */

/* assignment operator */
template <class TYPE, typename attribute>
binary_search_tree<TYPE, attribute> &binary_search_tree<TYPE, attribute>::operator=(binary_search_tree<TYPE, attribute> &rhs) {
  if (this == &rhs) {
    return *this;
  } else {
    this->clear_tree(this->root);
  }

  this->copy_tree(this->root, rhs.root);

  return *this; 
}


/* private recursive functions */

/* insert a type into the tree */
template <class TYPE, typename attribute>
bool binary_search_tree<TYPE, attribute>::insert(node<TYPE> * &root, TYPE &to_add) {
  if (!root) { /* found the insertion point */
    root = new node<TYPE>(to_add);
    if (!root)
      return false;

    /* success */
    return true;
  }

  /* keep going through the tree */
  if (to_add < root->get_data()) {
    return this->insert(root->get_left(), to_add);
  } else {
    return this->insert(root->get_right(), to_add);
  }
  
  return false;
}


/* copy one tree from another node by node */
template <class TYPE, typename attribute>
void binary_search_tree<TYPE, attribute>::copy_tree(node<TYPE> * &dest, node<TYPE> * &src) {
  if (!src) {
    return;
  }

  this->insert(dest, src->get_data());
  this->copy_tree(dest->get_left(), src->get_left());
  this->copy_tree(dest->get_right(), src->get_right());
}


/* recursively search through a route populating a list with matches */
template <class TYPE, typename attribute>
void binary_search_tree<TYPE, attribute>::search(node<TYPE> * &root, attribute &key, std::list<TYPE> &result) {
  if (!root) return;
  
  if (root->get_data() == key) {
    result.emplace_front(root->get_data());
  }

  /* if the root's data is less than the key (key is greator than or equal to root's data), go right. */
  if (root->get_data() < key) {
    this->search(root->get_right(), key, result); /* next recursive call */
  } else { /* if the root's data is greator than the key (key is less than root's data), go left. */
    this->search(root->get_left(), key, result); /* next recursive call */
  }
}


/* get the inorder successor and remove it, saving the ios */
template <class TYPE, typename attribute>
void binary_search_tree<TYPE, attribute>::get_ios_and_delete(node<TYPE> * &root, TYPE &res) {
  if (!root) /* no node */
    return;
  else if (!root->get_left()) { /* found ios */
    res = root->get_data(); /* copy data */

    /* delete node, set it's parent to adopt get_right() pointer if get_right() exists */
    node<TYPE> *tmp = root->get_right();
    delete root;
    root = tmp;

    /* unravel stack */
    return;
  }

  /* keep going down the tree */
  return this->get_ios_and_delete(root->get_left(), res);
}


/* remove all of matching attribute */
template <class TYPE, typename attribute>
bool binary_search_tree<TYPE, attribute>::remove(node<TYPE> * &root, attribute &key) {
  if (!root) /* no node to check */
    return 0;

  /* post order */
  int count = this->remove(root->get_left(), key);
  count += this->remove(root->get_right(), key);

  /* if root has a matching course */
  if (root->get_data() == key) {
    ++count;

    /* if root is a leaf */
    if (!root->get_left() && !root->get_right()) {
      delete root;
      root = NULL;
    } else if ((root->get_left() || root->get_right()) && !(root->get_left() && root->get_right())) { /* if root has one child */
      node<TYPE> *tmp;
      if (root->get_left())
        tmp = root->get_left();
      else
        tmp = root->get_right();

      delete root;
      root = tmp;
    } else { /* if root has two children */
      TYPE ios;
      this->get_ios_and_delete(root->get_right(), ios);
      root->set_data(ios);
    }
  }

  return count;
}


/* clear a tree */
template <class TYPE, typename attribute>
void binary_search_tree<TYPE, attribute>::clear_tree(node<TYPE> * &root) {
  if (!root) /* base case */
    return;

  /* get to the leaves first */
  this->clear_tree(root->get_left());
  this->clear_tree(root->get_right());

  /* if we are a leaf */
  if (!root->get_left() && !root->get_right()) {
    delete root;
    root = NULL;
  }
}


/* recursively prints out a tree */
template <class TYPE, typename attribute>
void binary_search_tree<TYPE, attribute>::display(node<TYPE> *root) {
  if (!root) return;

  this->display(root->get_left());
  std::cout << std::endl << root->get_data() << std::endl;
  this->display(root->get_right());
}


/* Returns the height of the tree */
template <class TYPE, typename attribute>
int binary_search_tree<TYPE, attribute>::get_height(node<TYPE> *root) {
  if (!root) /* no node to count */
    return 0;
  if (!root->get_left() && !root->get_right()) /* got to a leaf */
    return 1;

  /* get distances down the tree */
  int left_dist = 1 + this->get_height(root->get_left());
  int right_dist = 1 + this->get_height(root->get_right());

  /* compare distances, returning larger one */
  if (right_dist >= left_dist)
    return right_dist;

  return left_dist;
}

