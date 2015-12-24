#pragma once
#include "../atom.h"


class Potential {
public:
    Potential();

    virtual void computeForces(Atom* atoms, int n) = 0;
};

