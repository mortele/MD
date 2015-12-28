#pragma once
#include "integrator.h"

class VelocityVerlet : public Integrator {
public:
    VelocityVerlet(double dt);
    void advance(Atom *atoms, int n);

private:
    bool firstStep = false;
};

