#pragma once
#include "potential.h"
#include <cmath>


class Gravitational : public Potential {
public:
    Gravitational(double G);
    Gravitational(double G, double eps);
    void   computeForces(Atom *atoms, int n);
    double computePotential(Atom *atoms, int n);
    std::string getName() { return "Gravitational"; }

private:
    double G;
    double eps;
};

