#pragma once
#include "../atom.h"

class Integrator {
public:
    Integrator(double dt);
    virtual void advance(Atom* atoms, int n) = 0;

    double dt;
};
