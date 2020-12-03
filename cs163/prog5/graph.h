/*
 * Jack Thake, Karla Fant, CS163
 * This File holds the declarations for the graph class and it's required
 * structures.
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <cstddef>

/* one vertex */
struct vertex {
  /* 
   * vertex's data, it does not say in the assignment exactly how much data per course we need, 
   * I just went with the course's name.
  */
  char *data; 
  struct node *head; /* adjacency list */
};


/* one node in adjacency list */
struct node {
  vertex *adj; /* pointer to adjacent vertex */
  node *next; /* next node */
};


/* one graph */
class graph {
  public:
    graph(size_t size=5); /* constructor */
    ~graph(void); /* deconstructor */

    int insert_course(const char *to_add); /* insert course */
    int insert_edge(const char *current, const char *connect); /* insert edge between two courses */
    int display(const char *current); /* display graph */
    int destroy_all(void); /* deallocate */

  private:
    int get_location(const char *to_find); /* returns an index to the matching vertex */
    void display_recurs(vertex *current, bool is_first);
    
    vertex *adjacency_list;
    bool *visited;
    size_t len;
};

#endif
