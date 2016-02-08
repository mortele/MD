#include "integrator.h"
#include "../Potentials/potential.h"
#include "../system.h"

Integrator::Integrator(real dt, System* system) {
    m_dt = dt;
    m_system = system;
}

void Integrator::setPotential(Potential* potential) {
    m_potential = potential;
}

