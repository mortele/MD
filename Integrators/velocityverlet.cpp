#include "velocityverlet.h"
#include "../Potentials/potential.h"
#include "../system.h"

VelocityVerlet::VelocityVerlet(double dt, System* system) : Integrator(dt) {
    this->firstStep = true;
    this->dtHalf = dt/2.0;
    this->system = system;
}

void VelocityVerlet::advance(Atom* atoms, int n) {
    if (this->firstStep) {
        this->potential->computeForces(atoms, n);
        this->firstStep = false;
        this->periodicBoundaryConditions = system->getPeriodicBoundaryConditions();
    }
    for (int i=0; i < n; i++) {
        atoms[i].setVelocity(atoms[i].getVelocity() + (this->dtHalf/atoms[i].getMass()) * atoms[i].getForce());
        atoms[i].setPosition(atoms[i].getPosition() + this->dt                          * atoms[i].getVelocity());
    }
    if (this->periodicBoundaryConditions) {
        this->system->applyPeriodicBoundaryConditions();
    }
    this->potential->computeForces(atoms, n);
    for (int i=0; i < n; i++) {
        atoms[i].setVelocity(atoms[i].getVelocity() + (this->dtHalf/atoms[i].getMass()) * atoms[i].getForce());
    }
}

