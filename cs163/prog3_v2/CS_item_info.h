#ifndef CS_ITEM_INFO_H
#define CS_ITEM_INFO_H

#include "CS_error.h"

#include <fstream>
using namespace std;

class CS_item_info {
  public:
    CS_item_info(void);
    CS_item_info(ifstream &);
    ~CS_item_info(void);

    CS_error print(void) const;
    inline bool is_valid() const { return *this->name; };

    void operator=(const CS_item_info &to_copy);
    bool operator==(const char *) const;
  private:
    char *name, *location, *hints;
};

#endif

