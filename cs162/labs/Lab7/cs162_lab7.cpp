#include "cs162_list.h"

//Start in Step 3 by uncommenting out the code to create 
//a list object and build it!

int main()
{
    //Create an object of class list
    list my_list;

    //Call the build function to create a Linear Linked List
    //(The build member function has already been written)
    my_list.build();


    //Place your code here to call the functions for Lab #7
    cout << "Printing all" << endl;
    my_list.display_all();
    cout << endl << endl;

    cout << "Counting occurances of the first item" << endl;
    cout << my_list.count_first() << endl;
    cout << endl << endl;

    cout << "Display the last item" << endl;
    my_list.display_last();
    cout << endl << endl;

    cout << "Are there multiple of the last item? 1 = yes, 0 = no" << endl;
    cout << my_list.find_last() << endl;
    cout << endl << endl;

    return 0;
}
