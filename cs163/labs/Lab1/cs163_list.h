#include <cstring>
#include <cctype>
#include <iostream>
#include <cstdlib>


//The data structure is a linear linked list of integers
//with a head AND tail pointer!
struct node
{
       int  data;
       node * next;
};

class list
{
      public:
             //These functions are supplied for you
             list();
             ~list();
             void build();
             void display_all();
            
             //****************************************************
             //Write each of these functions Iteratively and Recursively
             int sum_total();		      //Iterative
             int sum_total(node * head);  // Recursive

	         bool remove_last();          //Iterative
             bool remove_last(node * & head, node * & tail);  //Recursive

             bool remove_all();                 //Iterative
             bool remove_all(node * & head);    //Recursive

             bool find_item(int item_to_find);  //Iterative
             bool find_item(node * head, int item_to_find);   //Recursive

             bool copy(list & from);            //Iterative
             bool copy(node * & dest_head, node * & dest_tail, node * source); //Recursive

      
      private:
             //Notice there is BOTH a head and tail pointer
             //Make sure to keep both properly maintained
              node * head;
	          node * tail;
};
             
