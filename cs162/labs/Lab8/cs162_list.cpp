#include "cs162_list.h"


//Implement the following functions for Lab #8

//Insert a node at the beginning of a linear linked list
void list::insert(int to_add)
{
	//Step #5 - Write the code here
  node *temp = this->head;
  this->head = new node;

  this->head->data = to_add;
  this->head->next = temp;
}

//Count the number of nodes in the LLL, returning the result
//Add a new node to the front of the list
//with the count as the data member
int list::count_and_insert()
{
     	//Step #6 - Write the code here
    int count;
    node *current = this->head;

    while(current) {
      ++count;
      current = current->next;
    }

    this->insert(count);
}

//Append a node to the end of a linear linked list
void list::append(int to_add)
{
        //Step #7 - Write the code here
  node *current = this->head;
  while(current->next) {
    current = current->next;
  }

  current->next = new node;
  current->next->data = to_add;
  current->next->next = nullptr;
}


//Remove the last node from the list
void list::remove_last()
{
   	//Step #7 - Write the code here
    node *current = this->head;

    while(current->next->next)
      current = current->next;

    delete current->next;
    current->next = nullptr;
}

//Deallocate all nodes (Destructor)
list::~list()
{
        //Step #8 - Write the code here
    node *current, *next = this->head;

    while(next) {
      current = next;
      next = next->next;

      delete current;
    }
}

//Challenge - 
void list::copy_last()
{
  node *current = this->head;
  while(current->next) {
    current = current->next;
  }

  this->insert(current->data);
}      

