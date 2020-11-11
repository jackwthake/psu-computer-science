#ifndef CS_ITEM_QUEUE
#define CS_ITEM_QUEUE

#include "CS_item_info.h"
#include "CS_error.h"

class CS_item_queue {
  public:
    CS_item_queue();
    ~CS_item_queue();

    CS_error enqueue(const CS_item_info &);
    CS_error dequeue(CS_item_info &);
    CS_error peak(CS_item_info &) const;
    CS_error display() const;

    inline bool is_empty() const { return !qptr; }
  private:
    struct node {
      CS_item_info data;
      node *next;
    };

    void display_recurs(node *current) const;
    node *qptr;
};

#endif

