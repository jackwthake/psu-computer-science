//Put your header comments here with your name, class
//and purpose of the program
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

// ***************************************** 
//Place your prototypes here:
void get_user_input(const char prompt[], float &result);
void get_user_prices(float &padding_price, float &carpet_price, float &install_price);


int main() {
    float width, length, area;
    float carpet_price, padding_price, install_price;

    get_user_input("Please enter the room's width in feet: ", width);
    get_user_input("Please enter the room's length in feet: ", length);

    area = width * length;

    get_user_prices(carpet_price, padding_price, install_price);

    cout << "\n\n--- Pricing Report ---\n"
         << "Room entered was " << area << " square feet\n"
         << "$" << area * carpet_price << " total for carpetting with a price per square foot of $" << carpet_price << "\n" 
         << "$" << area * padding_price << " total for padding with a price per square foot of $" << padding_price << "\n" 
         << "and $" << install_price << " for the installation\n"
         << "Giving you a total of $" << (area * carpet_price) + (area * padding_price) + install_price << endl; 

    return 0;
}

//Now implement the functions here:
void get_user_input(const char prompt[], float &result) {
    cout << prompt;
    cin >> result;
    cin.ignore(100, '\n');
}

void get_user_prices(float &padding_price, float &carpet_price, float &install_price) {
    get_user_input("Please enter the price of the padding in square feet: $", padding_price);
    get_user_input("Please enter the price of the carpetting in square feet: $", carpet_price);
    get_user_input("Please enter the price of installation: $", install_price);
}
