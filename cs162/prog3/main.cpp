#include <iostream>
using namespace std;

#include "list.h"
#include "pizza.h"

int main(void) {
  Pizza pizza = { "test", "tset", "test", "test", 3, 2.f  };
  Pizza pizza1 = { "test1", "tset", "test", "test", 3, 2.f  };
  Pizza pizza2 = { "test2", "tset", "test", "test", 3, 2.f  };
  Pizza pizza3 = { "test3", "tset", "test", "test", 3, 2.f  };
  list pizzas;

  pizzas.add(pizza);
  pizzas.add(pizza1);
  pizzas.add(pizza2);
  pizzas.add(pizza3);


  cout << "first print" << endl;
  pizzas.display_all();

  pizzas.remove(pizza3.name);
  cout << "second print" << endl;
  pizzas.display_all();
  
  pizzas.add(pizza3);
  cout << "third print" << endl;
  pizzas.display_all();


  if(pizzas.exists(pizza3.name))
    cout << "Pizza 3 exists" << endl;

  if(!pizzas.exists("jshdgfsljdflf"))
    cout << "Doesn't exist." << endl;

  return 1;
}
