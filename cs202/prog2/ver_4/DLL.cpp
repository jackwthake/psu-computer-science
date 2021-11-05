#include "DLL.h"

#include <cstddef>
#include <cstring>
#include <iostream>

#include "assignment.h"
#include "in_person_class.h"
#include "remote_assistance.h"

using namespace std;


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


/*
 * recursively remove a node from a list
 * Use RTTI to check if the removed activity is an assignment, if it is - add it onto the completed assignment
 * vector.
*/
static bool remove_activity(node * &head, psu_activity &targ, std::vector<assignment> &completed_assignments) {
  if (!head) return false; // base case
  if (*head == targ) { // if we've found the right match, delete it
    node *prev = head->get_prev();
    node *next = head->get_next();

    // check if we're removing an assignment
    if (assignment *a = dynamic_cast<assignment *>(head->get_data())) {
      completed_assignments.push_back(assignment(*a)); // copy assignment to the completed vector
    }

    delete head;
    head = NULL;

    if (prev) // if there is a previous node, attach it to the next
      prev->set_next(next);
    if (next) // if there is a next node, attach it to the previous
      next->set_prev(prev);

    return true;
  }

  return remove_activity(head->get_next(), targ, completed_assignments);
}


/* recursively retrieve an activity */
static psu_activity *get_activity(node *head, char *name) {
  if (!head) return nullptr;
  if (strcmp(head->get_data()->get_name(), name) == 0) {
    return head->get_data(); 
  }

  return get_activity(head->get_next(), name);
}


/* recursively display a list */
static void display(node *head) {
  if (!head) return;
  
  head->get_data()->display();
  cout << "------------------" << endl;
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
  if (assignment *a = dynamic_cast<assignment*>(data))
    this->data = new assignment(*a);
  if (in_person_class *a = dynamic_cast<in_person_class*>(data))
    this->data = new in_person_class(*a);
  if (remote_assistance *a = dynamic_cast<remote_assistance*>(data))
    this->data = new remote_assistance(*a);
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
void node::set_next(node *next) {
  this->next = next;
}


/* set the previous node */
void node::set_prev(node *prev) {
  this->prev = prev;
}



/* return the data */
psu_activity *node::get_data(void) {
  return this->data;
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


/* Insert into the DLL */
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
 * using RTTI, if a removed activity is an assignment, push it to the completed assignment vector
*/
bool activity_list::remove_activity(psu_activity &to_remove, std::vector<assignment> &completed_assignments) {
  for (int i = 0; i < this->length; ++i) {
    if (this->head[i]) {
      if (::remove_activity(this->head[i], to_remove, completed_assignments))
        return true; 
    }
  }

  return false;
}


/* Get an activity based off of it's name */
psu_activity *activity_list::get_activity(char *name) {
  for (int i = 0; i < this->length; ++i) {
    if (this->head[i]) {
      psu_activity *ptr = ::get_activity(this->head[i], name);
      if (ptr) {
        return ptr;
      }
    }
  } 

  return nullptr;
}


/* clear the list */
bool activity_list::clear_all(void) {
  for (int i = 0; i < this->length; ++i) {
    clear_list(this->head[i]);
  }  

  delete []this->head;

  return true;
}


/* Display the list */
bool activity_list::display(void) {
  for (int i = 0; i < this->length; ++i) {
    if (this->head[i]) { // if there is a list, print it
      cout << "---- Priority " << i << " ----" << endl;
      ::display(this->head[i]);
    } else { // if there isn't a list, indicate it
      cout << "List with priority " << i << " is empty." << endl << "------------------" << endl;
    }
  }

  return true;
}

