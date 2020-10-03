#include "cs163_list.h"
using namespace std;

int main()
{
    
    //First try this out as is. Then start adding in your function calls!
  list my_list, list_2;
    my_list.build();
    my_list.display_all();

    //PLACE YOUR FUNCTION CALL HERE!
	cout << "Sum: " << my_list.sum_total() << endl;
	cout << "Removed last: " << my_list.remove_last() << endl;
	cout << "Is 60 in the list? " << my_list.find_item(60) << endl;
	cout << "Copy to second list: " << list_2.copy(my_list) << endl;
	cout << "Removed all: " << my_list.remove_all() << endl;
	cout << "Copied list" << endl;
	list_2.display_all();
	
    my_list.display_all();
    return 0;    
}
