#pragma once
#include "../atom.h"

class InitialCondition {
public:
    InitialCondition();

    virtual void  setupInitialCondition() = 0;
    Atom* getAtoms() { return this->atoms; }
    int   getN() { return this->n; }
    virtual std::string getName() = 0;

protected:
    int   n;
    Atom* atoms;
    bool  setupDone;
};

