#pragma once
#include <cmath>
#include "potential.h"
#include "../atom.h"

class LennardJones : public Potential {
public:
    LennardJones(double epsilon, double sigma);

    void computeForces(Atom* atoms, int n);

private:
    double epsilon;
    double sigma;
    double sigma6;
    double sigma12;
};

