#pragma once
#include "../atom.h"
#include "../Potentials/potential.h"
#include <string>
#include <vector>

class Integrator {
public:
    Integrator(real dt);
    virtual void advance(const std::vector<Atom*> & atoms, int n) = 0;
    void   setPotential(Potential* potential);
    real getTimeStep() { return m_dt; }
    virtual std::string getName() = 0;

protected:
    Potential*  m_potential;
    real      m_dt;
};
