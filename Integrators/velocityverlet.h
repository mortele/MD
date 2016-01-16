#pragma once
#include "integrator.h"

class System;

class VelocityVerlet : public Integrator {
public:
    VelocityVerlet(double dt, System* system);
    void advance(Atom *atoms, int n);
    std::string getName() { return "Velocity Verlet"; }

private:
    double  dtHalf;
    bool    firstStep;
    bool    periodicBoundaryConditions;
    System* system;
};

