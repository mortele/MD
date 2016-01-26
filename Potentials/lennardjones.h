#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include "potential.h"
#include "../atom.h"
#include "../vec.h"

class LennardJones : public Potential {
public:
    LennardJones(double epsilon,
                 double sigma,
                 std::vector<double> systemSize,
                 class System* system);

    LennardJones(double epsilon,
                 double sigma,
                 std::vector<double> systemSize,
                 double rCut,
                 class System* system);

    void   computeForces    (const std::vector<Atom*> & atoms, int n);
    double computePotential (const std::vector<Atom*> & atoms, int n);
    std::string getName() { return "Lennard-Jones"; }

private:
    double m_epsilon = 0;
    double m_sigma = 0;
    double m_sigma6 = 0;
    double m_potentialEnergy = 0;
    double m_24epsilonSigma6 = 0;
    double m_4epsilonSigma6 = 0;
    double m_potentialAtCut = 0;
    std::vector<double> m_systemSize;
};

