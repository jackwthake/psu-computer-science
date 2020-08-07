#include "cs162_list.h"


int main()
{
    list my_values;
    
    my_values.build();

    //PUT YOUR FUNCTION CALL HERE!
    my_values.insert(50);
    my_values.insert(50);
    my_values.insert(50);
    my_values.insert(50);
    my_values.insert(50);
    my_values.append(60);
    my_values.count_and_insert();
    my_values.display_all();
    my_values.remove_last();
    my_values.display_all();
    my_values.copy_last();
    my_values.display_all();
     
    return 0;

}
