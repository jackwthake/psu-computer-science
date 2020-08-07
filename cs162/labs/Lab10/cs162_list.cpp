#include "cs162_list.h"
#include <iostream>
using namespace std;


//These are the functions to implement for this lab
//Like Lab9, we are not using clases here

//Check to see if the desired item is in the list
//Return true if it is found

//We are also practicing with returning values; make
//sure to return values from your functions and use
//those returned values in main!

//Step 2 - Practice Traversal
int display_first_and_last(node * head)
{

  node *current = head;
           //Write your code here
  cout << head->data << '\t';

  while(current->next)
    current = current->next;

  cout << current->data << endl;
}

//Step 3 - Practice Insertion
bool insert_before_last(node * & head, int to_add)
{
    node *current = head;
    node *temp;
           //Write our code here
    if(!head->next)
      return false;

    while(current->next->next) {
      current = current->next;
    }

    temp = current->next;

    current->next = new node;
    current->next->data = to_add;
    current->next->next = temp;
}

//Step 4 - Practice Removal
int remove_first_two(node * & head)
{
          //Write your code here
    int removed = 1;
    node *current = head;

    while(current && removed <= 2) {
      node *temp = head;
      head = temp->next;
      delete temp;

      ++removed;
      current = current->next;
    }

    return removed;
}


//Challenge - Make a complete copy  of the entire LLL creating
//a completely new LLL
void copy_all(node * & destination_head, node * source_head)
{
          //Write your code here
    node *dest_curr = destination_head;
    while(dest_curr->next) {
      dest_curr = dest_curr->next;
    }

    dest_curr->next = source_head;
    
}
