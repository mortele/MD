#pragma once
#include "integrator.h"

class VelocityVerlet : public Integrator {
public:
    VelocityVerlet(double dt);
    void advance(Atom *atoms, int n);
    std::string getName() { return "Velocity Verlet"; }

private:
    bool firstStep = false;
};

