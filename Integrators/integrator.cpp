#include "integrator.h"

Integrator::Integrator(real dt) {
    m_dt = dt;
}

void Integrator::setPotential(Potential* potential) {
    m_potential = potential;
}

