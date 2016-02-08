#pragma once
#include <tgmath.h>
#include <iostream>
#include <vector>
#include "potential.h"
#include "../atom.h"
#include "../vec.h"

class LennardJonesNeighbourLists : public Potential {
public:
    LennardJonesNeighbourLists(std::vector<real>, real, class System*);
    LennardJonesNeighbourLists(real, real, std::vector<real>, real, real, class System*);
    void   computeForces    (const std::vector<Atom*> & atoms, int n);
    real computePotential (const std::vector<Atom*> & atoms, int n);
    real getPressure () { return m_pressure; }
    std::string getName() { return "Lennard-Jones"; }

private:
    real m_epsilon = 0;
    real m_sigma = 0;
    real m_sigma6 = 0;
    real m_potentialEnergy = 0;
    real m_24epsilon = 0;
    real m_4epsilonSigma6 = 0;
    real m_potentialAtCut = 0;
    std::vector<real> m_systemSize;
    std::vector<real> m_systemSizeHalf;
};

