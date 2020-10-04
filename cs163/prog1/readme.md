Jack Thake • CS163 • Karla Fant • 10.3.20 • 647 words

# Design Write up for Program One
This program will contain several classes and structures representing a list of
home improvement projects. At the highest level, all projects will be split up
into groups sorted by their priority, from highest priority to lowest. each
group of a given priority will be a Linear Linked List. Each node of one of the
respective lists will contain the following: The structure containing all of the
project's data and a pointer, that points to the next node in the list.

---
## Class structure
To achieve this structure the following will be implemented:
- A manager class that holds the lists of projects by priority.
- A list class which will manage the Linear Linked List's memory and nodes.
- A node structure containing an individual project and a pointer to the next
  list item.

---
## List Manager class
The purpose of the manager class will be to interface with the individual Linear
Linked Lists. It will have the following exposed public member functions:
- **constructor**: Takes in the number of priority levels to be used, initializes.
  all N of the priority lists. Keeps itself shielded by not exposing the Lists
  to the function caller. It will return nothing.
- **destructor**: Will take no parameters and will simply oversee the
  deallocation of all the member lists. It will return nothing.
- **add_item**: Will take a reference to an already created project structure, as
  well as that project's priority level. It will then add that project to the
  respective list, if the list doesn't exist, the function will return false
  to indicate an error. Otherwise the item is passed to the list's add_item
  function and the function will return it's return code. In no part of this
  process will the caller gain access to any of the hidden infrastructure.
- **display_priority**: Will take an integer value representing the priority
  levels to display to the user. If that list exists, call it's print
  function and return true. If the rating does not have an associated
  priority, return false. This process will never allow the caller access to
  any members.
- **display_all**: Will take no parameters, and will loop through all the member
  lists calling each's print function. This will only return false if none of
  the lists have nodes. This process will never allow the caller access to
  any members.

---
## Linear Linked List class
One individual linked list. This will contain a head pointer that points to the
first node, as well as all functionality with dealing with the linked list. It
will contain the following exposed public member functions:
- **constructor**: Will take no arguments and will initialize all member
  variables.
- **destructor**: Will take no arguments and will oversee the deallocation of
  all dynamically allocated memory
- **add_item**: Will take in a reference to an initialized project structure. It
  will add the passed structure to the list, if successful return true,
  Otherwise returning false.
- **display_all**: Will take no arguments, simply print all nodes in the list
  to the console. This function will only return false if the link is empty.

---
## Node Structure
The node structure holds one item in the linear linked list as well the link to
the next node in the list. These will be represented as:
- **data**: Represents one individual project.
- **next**: Holds a pointer to the next node in the list, NULL if it is the
  last node.

---
## Project Structure
The project structure will contain all of the information regarding one
individual project. It will hold the following members:
- **name**: The name of the project.
- **estimated cost**: The total estimated cost of the whole project.
- **length of project**: How much time (in days) the project will take before
  completion.
- **hired workers**: This will contain the name of any workers, or companies
  contracted for the work.
- **completion date**: The estimated date of completion for the whole project.
