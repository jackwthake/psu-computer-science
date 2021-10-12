#ifndef __GATE_H__
#define __GATE_H__

#include "location.h"

class gate : public location {
  public:
    gate();
    gate(char *identifier);

    ~gate();

    // TODO: Implement function definitions
    // FATAL: Including plane.h vauses compilation to fail.
};

#endif

