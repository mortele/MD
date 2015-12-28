#pragma once
#include "../atom.h"

class InitialCondition {
public:
    InitialCondition();

    virtual void  setupInitialCondition() = 0;
    virtual Atom* getAtoms() = 0;
    int   getN() { return this->n; }

protected:
    int   n;
    Atom* atoms;
    bool  setupDone;
};

