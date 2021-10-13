#ifndef VISITOR_H
#define VISITOR_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"

/* a visitor can visit any of my specific data types */
class Visitor {
  //FILL IN
  public: 
    virtual void visit(shared_ptr<demogData> d) = 0;
    virtual void visit(shared_ptr<psData> ps) = 0;
    virtual void visit(shared_ptr<psCombo> pc) = 0;
};
#endif

