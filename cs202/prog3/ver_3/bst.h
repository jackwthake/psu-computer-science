#ifndef __BST_H__
#define __BST_H__

template <class TYPE, typename attribute>
class binary_search_tree {
  public:
    binary_search_tree();
    binary_search_tree(const binary_search_tree &);

    ~binary_search_tree();

    void insert(TYPE &);
    void search(attribute &, std::list<TYPE> &);
    bool remove(attribute &);

    void display_all();
    int get_height();

    /* operators */
    binary_search_tree operator=(const binary_search_tree &);

  private:
    class node {
      public:
        node();
        node(TYPE &data);

        node * &get_left();
        node * &get_right();
        void set_left(node *);
        void set_right(node *);

        TYPE &get_data();
      private:
        TYPE data;
        node *left, *right;
    };

    /* recursive functions */
    bool insert(node * &root, TYPE &); // insert a type into the tree
    bool copy_tree(node * &dest, node * &src);
    void search(node * &root, attribute &, std::list<TYPE> &); // search the tree by the attribute, populating a list
    
    void get_ios_and_delete(node * &root, TYPE &); // get the ios for the passed node and delete it, storing it in the reference
    bool remove(node * &root, attribute &); // remove by attribute
    void clear_list(node * &root);
    
    void display(node *root); // display tree
    int get_height(node *root); // get the tree's height

    node *root;
};

/* included for source code */
#include "bst.cpp"

#endif
