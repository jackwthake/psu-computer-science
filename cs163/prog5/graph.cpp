/*
 * Jack Thake, Karla Fant, CS163
 * This file holds the implementation for the graph class and it's static recursive functions.
*/

#include "graph.h"
#include <cstring>

#define UNUSED(x) (void)(x)

/*
 * Static recursive functions
*/

/* deallocate linear linked list */
static void delete_LLL_recurs(node * &head) {
  if (!head) return;

  delete_LLL_recurs(head->next);

  delete head;
};


/*
 * Member functions
*/

/* constructor */
graph::graph(size_t size) {
  this->len = size;
  this->adjacency_list = new vertex[this->len];

  for (size_t i = 0; i < this->len; ++i) {
    adjacency_list[i].data = NULL;
    adjacency_list[i].head = NULL;
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
  UNUSED(current);
  UNUSED(connect);

  return 0;
}


/* display all connections from a specific vertex */
int graph::display(const char *current) {
  UNUSED(current);

  return 0;
}


/* destroy graph */
int graph::destroy_all(void) {
  /* 
   * data to deallocate:  
   * 1. each node
   * 2. each node's string
   * 3. each node's LLL
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

