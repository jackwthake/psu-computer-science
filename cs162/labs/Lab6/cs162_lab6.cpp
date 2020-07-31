//Put your header comments here with your name, class
//and purpose of the program

#include "cs162_course.h"
#include <cstring>
#include <iostream>
using namespace std;

const int class_length = 5;


int main()
{

    //Step #4 - Create an object of the class here:
    course classes[5];
    char response = 0;
    int CRN = 0;

    //Steps #5-10 - Call the member functions here:
    for (int i = 0; i < class_length; ++i) {
        classes[i] = course();

        cout << "Class " << i + 1 << "\n" << endl;
        classes[i].read_course();
        cout << endl << endl;
    }

    for (int i = 0; i < class_length; ++i) {
        classes[i].display();
    }

    cout << "Would you like to drop a class? [Y/N]: ";
    cin >> response;
    cin.ignore(100, '\n');
    
    while(tolower(response) != 'n') {
        cout << "please enter the class CRN you are wishing to drop: ";
        cin >> CRN;
        cin.ignore(100, '\n');

        for(int i = 0; i < class_length; ++i) {
            if(classes[i].drop(CRN))
                break;
        }
        
        cout << "Would you like to drop a class? [Y/N]: ";
        cin >> response;
        cin.ignore(100, '\n');
    }

    for (int i = 0; i < class_length; ++i) {
        classes[i].display();
    }

    return 0;
}
