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
    double epsilon = 0;
    double sigma = 0;
    double sigma6 = 0;
    double sigma12 = 0;
    double potentialEnergy = 0;
    std::vector<double> systemSize;
};

