#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include "potential.h"
#include "../atom.h"
#include "../vec.h"

class LennardJones : public Potential {
public:
    LennardJones(double, double, std::vector<double>, double, class System*);
    void   computeForces    (const std::vector<Atom*> & atoms, int n);
    double computePotential (const std::vector<Atom*> & atoms, int n);
    double getPressure () { return m_pressure; }
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

