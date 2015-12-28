#include "integrator.h"

Integrator::Integrator(double dt) {
    this->dt = dt;
}

void Integrator::setPotential(Potential* potential) {
    this->potential = potential;
}

