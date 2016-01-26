#pragma once
#include "integrator.h"
#include <vector>

class System;

class VelocityVerlet : public Integrator {
public:
    VelocityVerlet(double dt, System* system);
    void advance(const std::vector<Atom*> & atoms, int n);
    std::string getName() { return "Velocity Verlet"; }

private:
    double  m_dtHalf;
    bool    m_firstStep;
    bool    m_periodicBoundaryConditions;
    System* m_system;
};

