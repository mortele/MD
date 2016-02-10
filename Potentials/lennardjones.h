#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include "potential.h"


class LennardJones : public Potential {
public:
    LennardJones(real epsilon, real sigma, std::vector<real> systemSize, real rCut, class System* system);

    void   computeForces();
    real computePotential();
    std::string getName() { return "Lennard-Jones"; }

private:
    real m_epsilon = 0;
    real m_sigma = 0;
    real m_sigma6 = 0;
    real m_sigma12 = 0;
    real m_potentialEnergy = 0;
    real m_rCut = 0;
    real m_rCut2 = 0;
    real m_potentialAtCut = 0;
    real m_24epsilon = 0;
    real m_4epsilonSigma6 = 0;
    std::vector<real> m_systemSize;
};
