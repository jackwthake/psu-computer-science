#include "cs162_list.h"

//These are the functions you will be writing
//Everything else has already been written for you!

//Constructor
list::list()
{
     //Step 3 - Implement the constructor here
  this->head = NULL;
}


//Display all items in a linear linked list
void list::display_all()
{
     //Step 5 - Implement the display_all function here
  node *current = this->head;
  while (current) {
    cout << current->data << endl;

    current = current->next;
  }
}


//Count the number of times the first node's data appears
//in the list, and return that count.
int list::count_first()
{
     //Step 6 - Implement the count_first here
     //(remember to return the count!
    int counter = 0;
    int tester = this->head->data;

    node *current = this->head;
    while(current) {
      if(current->data == tester)
        ++counter;

      current = current->next;
    }

    return counter;
}

//Display the LAST node's data
void list::display_last()
{
    //Step 7 - Place your code here
    node *current = this->head;
    while(current) {
      if(current->next == NULL)
        cout << current->data << endl;

      current = current->next;
    }
}

//Return true if the last node's data appears
//in the list more than once.
bool list::find_last()
{
    //Step 8 - Place your code here
    node *current = this->head;
    node *last_item = NULL;
    int last_item_data;

    while(current) {
      if(current->next == NULL) {
        last_item = current;
        last_item_data = current->data;
      }

      current = current->next;
    }

    current = this->head;

    while(current) {
      if(current != last_item) {
        if(current->data == last_item_data)
          return true;
      }

      current = current->next;
    }

    return false;
}
