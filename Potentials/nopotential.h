#pragma once
#include "potential.h"
#include <vector>
#include "../atom.h"

class NoPotential : public Potential {
public:
    NoPotential(class System* system);
    void    computeForces(std::vector<Atom*> atoms, int n) {}
    double  computePotential(std::vector<Atom*> atoms, int n) { return 0; }
    std::string getName() { return "None"; }
};


