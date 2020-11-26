#include "video_entry.h"
#include "video_tree.h"
#include <iostream>
#include <cstring>
using namespace std;

void read_in_field(const char *prompt, char *res, int len) {
  cout << prompt;
  cin.get(res, len, '\n');
  cin.ignore(100, '\n');
}


void read_in_entry(video_tree &tree) {
  video_entry entry;
  char media[51], course[51], desc[51], next[51];
  int length = 0;

  read_in_field("Please enter the media name: ", media, 51);
  read_in_field("Please enter the course name: ", course, 51);
  read_in_field("Please enter the description: ", desc, 51);
  read_in_field("Please enter the next item in the playlist: ", next, 51);
  
  cout << "Please enter the video's length in minutes: ";
  cin >> length;
  cin.ignore(100, '\n');

  video_entry tmp(course, media, desc, length, next);
  tree.insert(tmp);
}


int main(void) {
  video_tree tree;
  char conf = '\0';

  cout << "Start of insertion loop" << endl;

  do {
    cout << endl << endl;
    read_in_entry(tree);

    cout << "More to add? (y/n): ";
    cin >> conf; 
    cin.ignore(100, '\n');
  } while (tolower(conf) != 'n');

  cout << "Now printing tree" << endl;
  tree.display_all();
  cout << "Tree Height: " << tree.get_height() << endl;

  cout << "Start of search" << endl;

  do {
    char search_name[51];
    video_entry *arr = NULL;
    int len = 0;

    read_in_field("Please enter a course name: ", search_name, 51);
    tree.search(search_name, arr, len);

    if (arr) {
      cout << "Printing search results: " << endl;
      for (int i = 0; i < len; ++i) {
        cout << endl;
        arr[i].print();
      }
    } else {
      cout << "No matches found." << endl;
    }

    cout << "More to search? (y/n): ";
    cin >> conf; 
    cin.ignore(100, '\n');

    delete []arr;
  } while (tolower(conf) != 'n');

  cout << "Start of display" << endl;

  do {
    char search_name[51];

    read_in_field("Please enter a course name: ", search_name, 51);
    tree.display_course(search_name);

    cout << "More to display? (y/n): ";
    cin >> conf; 
    cin.ignore(100, '\n');
  } while (tolower(conf) != 'n');

  cout << "Start of Remove by media name" << endl;

  do {
    char key[51];
    read_in_field("Please enter in a media name you want to remove: ", key, 51);
    tree.remove(key);

    cout << "More to remove? (y/n): ";
    cin >> conf; 
    cin.ignore(100, '\n');
  } while (tolower(conf) != 'n');

  cout << "Now printing tree" << endl;
  tree.display_all();
  cout << "Tree Height: " << tree.get_height() << endl;

  cout << "Start of Remove by course name" << endl;

  do {
    char key[51];
    read_in_field("Please enter in a course name you want to remove: ", key, 51);
    tree.remove_course(key);

    cout << "More to remove? (y/n): ";
    cin >> conf; 
    cin.ignore(100, '\n');
  } while (tolower(conf) != 'n');

  cout << "Now printing tree" << endl;
  tree.display_all();
  cout << "Tree Height: " << tree.get_height() << endl;

  return 0;
}
