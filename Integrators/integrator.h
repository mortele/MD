#pragma once
#include "../atom.h"
#include "../Potentials/potential.h"
#include <string>
#include <vector>

class Integrator {
public:
    Integrator(double dt);
    virtual void advance(const std::vector<Atom*> & atoms, int n) = 0;
    void   setPotential(Potential* potential);
    double getTimeStep() { return this->dt; }
    double dt;
    virtual std::string getName() = 0;

protected:
    Potential* potential;
};
