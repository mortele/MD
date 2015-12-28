#pragma once
#include "../atom.h"
#include "../Potentials/potential.h"

class Integrator {
public:
    Integrator(double dt);
    virtual void advance(Atom* atoms, int n) = 0;
    void   setPotential(Potential* potential);
    double getTimeStep() { return this->dt; }
    double dt;

protected:
    Potential* potential;
};
