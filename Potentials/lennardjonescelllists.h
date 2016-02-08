#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include "potential.h"
#include "../atom.h"
#include "../vec.h"

class LennardJonesCellLists : public Potential {
public:
    LennardJonesCellLists(std::vector<double>, double, class System*);
    LennardJonesCellLists(double, double, std::vector<double>, double, class System*);
    void   computeForces();
    double computePotential();
    double getPressure () { return m_pressure; }
    std::string getName() { return "Lennard-Jones (Cell Lists)"; }

private:
    double m_epsilon = 0;
    double m_sigma = 0;
    double m_sigma6 = 0;
    double m_potentialEnergy = 0;
    double m_24epsilon = 0;
    double m_4epsilonSigma6 = 0;
    double m_potentialAtCut = 0;
    std::vector<double> m_systemSize;
    std::vector<double> m_systemSizeHalf;
};
