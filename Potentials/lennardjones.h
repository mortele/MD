#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include "potential.h"
#include "../atom.h"
#include "../vec.h"

class LennardJones : public Potential {
public:
    LennardJones(double epsilon, double sigma, std::vector<double> systemSize);

    void   computeForces(Atom* atoms, int n);
    double computePotential(Atom* atoms, int n);
    std::string getName() { return "Lennard-Jones"; }

private:
    double epsilon;
    double sigma;
    double sigma6;
    double sigma12;
    double potentialEnergy;
    std::vector<double> systemSize;
};

