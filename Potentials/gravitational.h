#pragma once
#include "potential.h"


class Gravitational : public Potential {
public:
    Gravitational(double G);
    void   computeForces(Atom *atoms, int n);
    //double computePotential(Atom *atoms, int n);

private:
    double G;
};

