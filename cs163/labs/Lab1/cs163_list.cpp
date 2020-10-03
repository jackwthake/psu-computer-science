#include "cs163_list.h"
using namespace std;

//Sum  all of the data together in a LLL
int list::sum_total()
{
  /*  node *current = this->head;
  int count = 0;

  while(current) {
	count += current->data;
	current = current->next;
  }*/

  int count = 0;
  count += sum_total(this->head);
  return count;
  
  //FIRST do this iteratively here. Then recursively
        //COMMENT out the iterative version when  rewriting
        //the solution recursively

        //To solve this recursively write another
        //function:   int sum_total(node * head);
        //and call it from this function
}

//Now implement the function recursively!
int list::sum_total(node * head)
{
  if(!head) { return 0; }
  return head->data + sum_total(head->next);
}

// *************************************************
//Remove the last node in a LLL. Return false if the
//list is empty and nothing is removed
bool list::remove_last()
{
  /*node *current = this->head;
  node *previous = NULL;

  if(!current) { return false; }
  while(current != this->tail) {
	previous = current;
	current = current->next;
  }

  // at the last node
  this->tail = previous;
  this->tail->next = NULL;
  delete current;*/

  if(!this->head) { return false; }
  return remove_last(this->head, this->tail);
  //Write your code here
        //FIRST do this iteratively here. Then recursively
        //COMMENT out the iterative version when  rewriting

}

//Now implement the function recursively!
bool list::remove_last(node * & head, node * & tail)
{
  // second to last item
  if(head->next == tail) {
	delete tail;
	head->next = NULL;
	this->tail = head;
	
	return true;
  }

  return remove_last(head->next, tail);
}

// ************************************************
//Remove all nodes in a LLL. Remove false if there is
//nothing to remove
bool list::remove_all()
{
  /*  node *current = head;

  if(!current) { return false; }
  
  while(current) {
	node *temp = current;
	current = current->next;

	delete temp;
  }

  this->head = NULL;*/
  if(!this->head) { return false; }
  if(remove_all(this->head)) {
	this->head = NULL;
	this->tail = NULL;
	return true;
  }
  
  //Remove all nodes in a LLL
 	//FIRST do this iteratively here. Then recursively
        //COMMENT out the iterative version when  rewriting

}

//Now implement the function recursively!
bool list::remove_all(node * & head)
{
  if(!head) { return true; }
  remove_all(head->next);
  delete head;

  return true;
}


// ************************************************
//Return true if the requested item (sent in as an argument)
//is in the list, otherwise return false
bool list::find_item(int item_to_find)
{
        //Write your code here
  if(!this->head) { return false; }
  return find_item(this->head, item_to_find);
}

//Now implement the function recursively!
bool list::find_item(node * head, int item_to_find)
{
  if(!head) { return false; }
  if(head->data == item_to_find) { return true; }

  return find_item(head->next, item_to_find);
}


// ************************************************
//Make a complete copy of a LLL
bool list::copy(list & from)
{
        //Write your code here
  // clear the dest list
  this->remove_all();
  return copy(this->head, this->tail, from.head);
}

//Now implement the function recursively
bool list::copy(node * & dest_head, node * & dest_tail, node * source)
{
  if(!source) {
	dest_tail = dest_head;
	return true;
  }
  
  dest_head = new node;
  dest_head->next = new node;
  
  dest_head->data = source->data;
  copy(dest_head->next, dest_tail, source->next);
}
