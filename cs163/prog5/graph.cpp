/*
 * Jack Thake, Karla Fant, CS163
 * This file holds the implementation for the graph class and it's static recursive functions.
*/

#include "graph.h"
#include <cstring>
#include <iostream>

using namespace std;

#define UNUSED(x) (void)(x)

/*
 * Static recursive functions
*/


/* add to the end of a linear linked list */
static void add_to_LLL_recurs(node * &head, vertex *to_add) {
  if (!head) { /* using pass by reference mechanism */
    head = new node; /* add in new node */
    head->adj = to_add; /* bring over data */
    head->next = NULL;

    return;
  }

  add_to_LLL_recurs(head->next, to_add);
}


/* deallocate linear linked list */
static void delete_LLL_recurs(node * &head) {
  if (!head) return; /* base case */

  /* move to the end of the list */
  delete_LLL_recurs(head->next);

  /* delete as we unwind stack frame */
  delete head;
};


/* display all connections */
void graph::display_recurs(vertex *current, bool is_first) {
  if (!current) return;

  int location = this->get_location(current->data);

  if (!this->visited[location]) {
    this->visited[location] = true;
    if (!is_first)
      cout << "Class: " << current->data << endl;

    node *curr = current->head;
    while (curr) {
      display_recurs(curr->adj, false);
      curr = curr->next;
    }
  }
}


/*
 * Member functions
*/


/* constructor */
graph::graph(size_t size) {
  this->len = size;

  /* allocate */
  this->adjacency_list = new vertex[this->len];
  this->visited = new bool[this->len];

  /* zero out array */
  for (size_t i = 0; i < this->len; ++i) {
    adjacency_list[i].data = NULL;
    adjacency_list[i].head = NULL;
    visited[i] = false;
  }
}


/* deconstructor */
graph::~graph(void) {
  this->destroy_all();
}


/* insert course to graph */
int graph::insert_course(const char *to_add) {
  size_t acc = 0;
  vertex *curr = this->adjacency_list;

  /* loop until we reach an empty vertex or, we run out of space */
  while (curr->data != NULL && acc < this->len)
    ++curr;

  /* if we have an empty vertex */
  if (curr->data)
    return 0;

  /* copy over, now we kknow the curr pointer is pointing to an empty vertex. */
  curr->data = new char[strlen(to_add) + 1]; 
  strcpy(curr->data, to_add);

  return 1;
}


/* insert connections between vertices */
int graph::insert_edge(const char *current, const char *connect) {
  int current_idx = this->get_location(current); /* get index's of vertices */
  int target_idx = this->get_location(connect);

  if (current_idx < 0 || target_idx < 0) /* only continue if both vertices exist */
    return 0;

  /* grab vertices from the list */
  vertex *curr = &this->adjacency_list[current_idx];
  vertex *targ = &this->adjacency_list[target_idx];

  /* add targ to the end of curr's LLL */
  add_to_LLL_recurs(curr->head, targ);

  return 1;
}


/* display all connections from a specific vertex */
int graph::display(const char *current) {
  int current_idx = this->get_location(current);
  if (current_idx < 0)
    return 0;

  for (size_t i = 0; i < this->len; ++i)
    this->visited[i] = false;

  cout << "Courses available after " << current << ":" << endl;
  display_recurs(&this->adjacency_list[current_idx], true);

  return 1;
}


/* destroy graph */
int graph::destroy_all(void) {
  /* 
   * data to deallocate:  
   * 1. each vertex's string
   * 2. each vertex's LLL
   * 3. the array itself
  */

  vertex *current;
  for (size_t i = 0; i < this->len; ++i) {
    current = &this->adjacency_list[i];

    if (current) {
      if (current->data)
        delete []current->data;

      /* deallocate LLL */
      delete_LLL_recurs(current->head);
    }
  }

  /* lastly deallocate array itself */
  delete []this->adjacency_list;

  return 1;
}


/* returns the location of a piece of data if it exists */
int graph::get_location(const char *to_find) {
  for (size_t i = 0; i < this->len; ++i) {
    if (this->adjacency_list[i].data) { /* only compare if the current string exists */
      if (strcmp(to_find, this->adjacency_list[i].data) == 0)
        return i; /* return index */
    }
  }

  return -1;
}

