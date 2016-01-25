#include "velocityverlet.h"
#include <vector>
#include <iostream>
#include "../Potentials/potential.h"
#include "../system.h"

using std::cout;
using std::endl;

VelocityVerlet::VelocityVerlet(double dt, System* system) :
        Integrator(dt) {
    this->firstStep = true;
    this->dtHalf = dt/2.0;
    this->system = system;
}

void VelocityVerlet::advance(std::vector<Atom*> atoms, int n) {
    if (this->firstStep) {
        this->potential->computeForces(atoms, n);
        this->firstStep = false;
        this->periodicBoundaryConditions = system->getPeriodicBoundaryConditions();
    }
    for (int i=0; i < n; i++) {
        for (int k=0; k<3; k++) {
            atoms.at(i)->addVelocity(this->dtHalf/atoms.at(i)->getMass() * atoms.at(i)->getForce().at(k), k);
            atoms.at(i)->addPosition(this->dt * atoms.at(i)->getVelocity().at(k), k);
        }
    }
    if (this->periodicBoundaryConditions) {
        this->system->applyPeriodicBoundaryConditions();
    }
    this->potential->computeForces(atoms, n);
    for (int i=0; i < n; i++) {
        for (int k=0; k<3; k++) {
            atoms.at(i)->addVelocity(this->dtHalf/atoms.at(i)->getMass() * atoms.at(i)->getForce().at(k), k);
        }
    }
}

