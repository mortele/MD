#pragma once
#include "integrator.h"
#include <vector>

class System;

class VelocityVerlet : public Integrator {
public:
    VelocityVerlet(real dt, System* system);
    void advance();
    std::string getName() { return "Velocity Verlet"; }

private:
    real    m_dtHalf;
    bool    m_firstStep;
    bool    m_periodicBoundaryConditions;
};

