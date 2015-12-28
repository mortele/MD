#pragma once
#include "initialcondition.h"
#include "../atom.h"

class TwoBody : public InitialCondition {
public:
    TwoBody();
    TwoBody(double);
    void  setupInitialCondition();
    Atom* getAtoms();

private:
    double e = 0.0;
};

