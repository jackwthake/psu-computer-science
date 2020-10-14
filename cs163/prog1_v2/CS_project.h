//
//  CS_project.h
//  psu-computer-science
//
//  Created by Jack Thake on 13/10/2020.
//  This file holds all declaration for list class
//

#ifndef CS_project_h
#define CS_project_h

typedef enum {
  SUCCESS,
  FAILURE,
  MEM_ALLOC_FAIL
} CS_error;

class CS_project {
public:
    CS_project();
    CS_project(char *name, char *workers, char *comp_date, float cost, int length, int coolness);
    ~CS_project();

    CS_error display() const;
    void operator=(const CS_project& proj);
private:
  char *name, *workers, *completion_date;
  float estimated_cost;
  int project_length, project_coolness;
};


#endif /* CS_project_h */
