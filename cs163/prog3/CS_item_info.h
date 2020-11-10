#ifndef CS_ITEM_INFO_H
#define CS_ITEM_INFO_H

class CS_item_info {
  public:
    CS_item_info();
    CS_item_info(const char *name, const char *location, const char *hints, const int rating);
    ~CS_item_info();

    bool print() const;

    void operator=(const CS_item_info &to_copy);
    bool operator==(const CS_item_info &test) const;
  private:
    char *name, *location, *hints;
    int rating;
};

#endif
