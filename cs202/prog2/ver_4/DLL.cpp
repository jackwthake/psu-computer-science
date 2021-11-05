#include "DLL.h"

#include <cstddef>
/*
 * Static recursive functions
*/

/* clear a list recursively */
static void clear_list(node * &head) {
  if (!head) return;

  node *tmp = head->get_next();
  delete head;

  clear_list(tmp);
}


/* recursively remove a node from a list */
static bool remove_activity(node * &head, psu_activity &targ) {
  if (!head) return false; // base case
  if (*head == targ) { // if we've found the right match, delete it
    node *prev = head->get_prev();
    node *next = head->get_next();

    delete head;
    head = NULL;

    if (prev) // if there is a previous node, attach it to the next
      prev->set_next(next);
    if (next) // if there is a next node, attach it to the previous
      next->set_prev(prev);

    return true;
  }

  return remove_activity(head->get_next(), targ);
}

    
/*
 * Node class implementation
*/

/* node constructor */
node::node(void) {
  this->data = NULL;
  this->prev = this->next = NULL;
}


/* normal constructor */
node::node(psu_activity *data) {
  this->data = data;
  this->prev = this->next = NULL;
}


/* returns the next node */
node * &node::get_next(void) {
  return this->next;
}


/* get previous */
node *node::get_prev(void) {
  return this->prev;
}



/* set the next node */
node *node::set_next(node *next) {
  this->next = next;
}


/* set the previous node */
node *node::set_prev(node *prev) {
  this->prev = prev;
}



/* return the data */
const psu_activity &node::get_data(void) {
  return *this->data;
}


/* overloaded operator equal */
bool node::operator==(const psu_activity &rhs) const {
  if (*this->data == rhs)
    return true;

  return false;
}


/*
 * activity_list implement
*/

/* default constructor */
activity_list::activity_list(void) {
  /* allocate array of DLL */
  this->head = new node*[this->length];

  /* zero out lists */
  for (int i = 0; i < this->length; ++i)
    this->head[i] = NULL;
}


/* destructor */
activity_list::~activity_list(void) {
  this->clear_all();
}


/*
 * Insert into the DLL
*/
bool activity_list::add_activity(psu_activity &to_add) {
  int priority = to_add.get_priority();

  if (priority < this->length) {
    node *tmp = this->head[priority];

    this->head[priority] = new node(&to_add);
    this->head[priority]->set_next(tmp);

    if (tmp)
      tmp->set_prev(this->head[priority]);

    return true;
  }

  return false;
}


/*
 * Remove a specific activity
*/
bool activity_list::remove_activity(psu_activity &to_remove) {
  for (int i = 0; i < this->length; ++i) {
    if (this->head[i]) {
      if (::remove_activity(this->head[i], to_remove))
        return true; 
    }
  }

  return false;
}


/* 
 * Get an activity based off of it's name
*/
bool activity_list::get_activity(char *name, psu_activity &result) {

}


/* 
 * clear the list
*/
bool activity_list::clear_all(void) {
  for (int i = 0; i < this->length; ++i) {
    clear_list(this->head[i]);
  }  

  delete []this->head;

  return true;
}


/*
 * Display the list
*/
bool activity_list::display(void) {

}

