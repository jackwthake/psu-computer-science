#include "cs162_list.h"
using namespace std;

int main()
{
    node * head = NULL;
    node * head2 = NULL;
    build(head);
    build(head2);
    display_all(head);

    //PLEASE PUT YOUR CODE HERE to call the function assigned
    display_first_and_last(head);
    insert_before_last(head, 20);
    remove_first_two(head);

    copy_all(head, head2);

    display_all(head);
    
    return 0;
}
