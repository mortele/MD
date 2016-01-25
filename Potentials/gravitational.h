#pragma once
#include "potential.h"
#include <cmath>


class Gravitational : public Potential {
public:
    Gravitational(double G);
    Gravitational(double G, double eps);
    void   computeForces(std::vector<Atom*> atoms, int n);
    double computePotential(std::vector<Atom*> atoms, int n);
    std::string getName() { return "Gravitational"; }

private:
    double G = 0;
    double eps = 0;
    double potentialEnergy = 0;
};

