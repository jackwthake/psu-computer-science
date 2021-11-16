#include "scheduler.h"
    

/* constructors */

/* default */
node::node() {
  this->left = this->right = NULL;
  this->data = event();
}


/* normal */
node::node(event &data) {
  this->data = data;
  this->left = this->right = NULL;
}


/* get left and right nodes */
node * &node::get_right() {
  return this->right;
}


node * &node::get_left() {
  return this->left;
}


/* set left and right nodes */
void node::set_right(node *right) {
  this->right = right;
}


void node::set_left(node *left) {
  this->left = left;
}


/* get the data in a node */
event *node::get_data() {
  return &this->data;
}

