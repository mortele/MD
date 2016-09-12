#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include "potential.h"
#include "../atom.h"
#include "../vec.h"

class GravitationalNeighbourLists : public Potential {
public:
    GravitationalNeighbourLists(real G, real eps, real rCut, real neighbourCut, System* system);
    void computeForces();
    real computePotential();
    std::string getName() { return "Gravitational (Neighbour Lists)"; }

private:
    real m_eps;
    real m_potentialEnergy = 0;
    real m_potentialAtCut = 0;
    std::vector<real> m_systemSize;
    std::vector<real> m_systemSizeHalf;
};

