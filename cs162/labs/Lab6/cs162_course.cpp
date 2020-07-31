//Include your name, course, and information about the code
//implemented in this file.

#include "cs162_course.h"
#include <cstring>
#include <iostream>
using namespace std;

//Implement the body of these functions for Lab #6
static void prompt_user(const char *prompt, char *response, int length) {
    cout << prompt;

    cin.width(length);
    cin.get(response, length, '\n');
    cin.ignore(100, '\n');
}

//Constructor - initialize all data members to their zero equivalent value
course::course()
{
	//Place the code for the constructor here
    for(int i = 0; i < SIZE; ++i) {
        first_name[i] = 0;
        last_name[i] = 0;

        section[i] = 0;
        designator[i] = 0;
    }

    CRN = 0;
}


//Read in the CRN, Course Description and Section
//Store these into the private data members of the class
void course::read_course()
{
        //Implement this function
        prompt_user("Please enter the student's first name: ", this->first_name, SIZE);
        prompt_user("Please enter the student's last name: ", this->last_name, SIZE);
        prompt_user("Please enter the course designator: ", this->designator, SIZE);
        prompt_user("Please enter the course section: ", this->section, SIZE);

        cout << "Please enter " << this->designator
             << "'s CRN: ";
        cin >> this->CRN;
}


//Display the name and course information
void course::display()
{
    cout << "--------------------------------------\n"
         << "Student: " << this->first_name << " " << this->last_name << "\n"
         << "CRN: " << this->CRN << "\n"
         << "Designator: " << this->designator << "\n"
         << "Section: " << this->section << "\n"
         << "--------------------------------------" << endl;
}

//Take the argument and compare it to the student's name
//If it is the same, return a true - otherwise return false
bool course::is_match(char a_first_name[], char a_last_name[])
{
       //Implement this function
    if(strcmp(this->first_name, a_first_name) == 0) {
        if(strcmp(this->last_name, a_last_name) == 0) {
            return true;
        }
    }

    return false;
}


//Reset the course information for a student if they
//want to drop, given the CRN. Only drop the course if the CRN
//matches. Return true if the operation was successful and false
//if the CRN doesn't match
bool course::drop(int CRN)
{
      //Implement this function 
    if(CRN == this->CRN) {
        this->CRN = 0;

        for(int i =0; i < SIZE; ++i) {
            this->designator[i] = 0;
            this->section[i] = 0;
        }

        return true;
    }

    return false;
}


