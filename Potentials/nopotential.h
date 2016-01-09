#pragma once
#include "potential.h"
#include "../atom.h"

class NoPotential : public Potential {
public:
    NoPotential() {}
    void    computeForces(Atom* atoms, int n) {}
    double  computePotential(Atom* atoms, int n) {}
    std::string getName() { return "None"; }
};

