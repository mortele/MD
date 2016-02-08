#pragma once
#include "potential.h"
#include <vector>
#include "../atom.h"

class NoPotential : public Potential {
public:
    NoPotential(class System* system);
    void    computeForces() {}
    real  computePotential() { return 0; }
    std::string getName() { return "None"; }
};


