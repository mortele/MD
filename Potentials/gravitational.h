#pragma once
#include "potential.h"
#include <cmath>


class Gravitational : public Potential {
public:
    Gravitational(double G, class System* system);
    Gravitational(double G, double eps, class System* system);
    void   computeForces    (const std::vector<Atom*> & atoms, int n);
    double computePotential (const std::vector<Atom*> & atoms, int n);
    std::string getName() { return "Gravitational"; }

private:
    double m_G = 0;
    double m_eps = 0;
    double m_potentialEnergy = 0;
};

