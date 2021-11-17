#ifndef __BST_H__
#define __BST_H__

#include <list>
    
template <class TYPE>
class node {
  public:
    node();
    node(TYPE &data);

    node * &get_left();
    node * &get_right();
    void set_left(node *);
    void set_right(node *);

    TYPE &get_data();
    void set_data(TYPE &);
  private:
    TYPE data;
    node *left, *right;
};


template <class TYPE, typename attribute>
class binary_search_tree {
  public:
    binary_search_tree();
    binary_search_tree(const binary_search_tree &);

    ~binary_search_tree();

    bool insert(TYPE &);
    void search(attribute &, std::list<TYPE> &);
    bool remove(attribute &);

    void display_all();
    int get_height();

    /* operators */
    binary_search_tree &operator=(const binary_search_tree &);

  private:
    /* recursive functions */
    bool insert(node<TYPE> * &root, TYPE &); // insert a type into the tree
    void copy_tree(node<TYPE> * &dest, const node<TYPE> * &src);
    void search(node<TYPE> * &root, attribute &, std::list<TYPE> &); // search the tree by the attribute, populating a list
    
    void get_ios_and_delete(node<TYPE> * &root, TYPE &); // get the ios for the passed node and delete it, storing it in the reference
    bool remove(node<TYPE> * &root, attribute &); // remove by attribute
    void clear_tree(node<TYPE> * &root);
    
    void display(node<TYPE> *root); // display tree
    int get_height(node<TYPE> *root); // get the tree's height

    node<TYPE> *root;
};

#endif
