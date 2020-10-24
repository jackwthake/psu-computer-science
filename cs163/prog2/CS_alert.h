//
//  CS_alert.h
//  psu-computer-science
//
//  Created by Jack Thake on 13/19/2020.
//  This file holds all declaration for stack class
//

#ifndef CS_ALERT_H
#define CS_ALERT_H

const int SIZE = 2;

/* denote error or success */
typedef enum {
  SUCCESS,
  FAILURE,
  MEM_ALLOC_ERROR
} CS_error;


/* used to hold one alert */
class CS_alert {
  public:
    CS_alert();
    CS_alert(const char *organization, const char *date, const char *time, const char *msg);
    ~CS_alert();

    CS_error display() const;
    void operator=(const CS_alert &copy);
    bool operator==(const CS_alert &test) const;
  private:
    char *organization, *date, *time, *msg;
};


/* holds a stack of alerts */
class CS_alert_stack {
  public:
    CS_alert_stack();
    ~CS_alert_stack();

    CS_error push(const CS_alert &to_add);
    CS_error pop(void);
    CS_error peak(CS_alert &to_add) const;
    CS_error display(void) const;
  private:
    struct node {
      CS_alert *data;
      node *next;
    };

    int top;
    node *head;
};

#endif

