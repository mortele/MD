#include "velocityverlet.h"
#include <vector>
#include <iostream>
#include "../Potentials/potential.h"
#include "../system.h"

using std::cout;
using std::endl;

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
    std::vector<double> velocity {0,0,0};
    std::vector<double> position {0,0,0};
    std::vector<double> force    {0,0,0};

    for (int i=0; i < n; i++) {

        velocity = atoms[i].getVelocity();
        position = atoms[i].getPosition();
        force    = atoms[i].getForce();

        for (int k=0; k<3; k++) {
            atoms[i].setVelocity(velocity.at(k) + this->dtHalf/atoms[i].getMass() * force.at(k) * velocity.at(k), k);
            atoms[i].setPosition(position.at(k) + this->dt * velocity.at(k), k);
        }
    }
    if (this->periodicBoundaryConditions) {
        this->system->applyPeriodicBoundaryConditions();
    }
    this->potential->computeForces(atoms, n);
    for (int i=0; i < n; i++) {
        velocity = atoms[i].getVelocity();
        force    = atoms[i].getForce();

        for (int k=0; k<3; k++) {
            atoms[i].setVelocity(velocity.at(k) + this->dtHalf/atoms[i].getMass() * force.at(k), k);
        }
    }
}

