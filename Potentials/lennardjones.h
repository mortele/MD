#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include "potential.h"


class LennardJones : public Potential {
public:
    LennardJones(double epsilon, double sigma, std::vector<double> systemSize, double rCut, class System* system);

    void   computeForces();
    double computePotential();
    std::string getName() { return "Lennard-Jones"; }

private:
    double m_epsilon = 0;
    double m_sigma = 0;
    double m_sigma6 = 0;
    double m_sigma12 = 0;
    double m_potentialEnergy = 0;
    double m_rCut = 0;
    double m_rCut2 = 0;
    double m_potentialAtCut = 0;
    double m_24epsilon = 0;
    double m_4epsilonSigma6 = 0;
    std::vector<double> m_systemSize;
};
