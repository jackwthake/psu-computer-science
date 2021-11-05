#include "assignment.h"
#include "in_person_class.h"
#include "remote_assistance.h"
#include "DLL.h"


int main(void) {
  assignment a1("10/9/21", "homework 4", 2);
  in_person_class c1("CS202", "Karla Fant", 202, 6, 1); 
  remote_assistance r1("12:00pm", "M/F", "Tutoring for CS251", 2, 1);
  activity_list ac1;

  ac1.add_activity(a1);

  return 0;
};
