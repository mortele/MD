#include "integrator.h"

Integrator::Integrator(double dt) {
    m_dt = dt;
}

void Integrator::setPotential(Potential* potential) {
    m_potential = potential;
}

