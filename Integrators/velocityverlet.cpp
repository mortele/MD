#include "velocityverlet.h"
#include <vector>
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
    std::vector<double> velocity {0,0,0};
    std::vector<double> position {0,0,0};
    std::vector<double> force    {0,0,0};

    for (int i=0; i < n; i++) {
        velocity = atoms[i].getVelocity();
        position = atoms[i].getPosition();
        force = atoms[i].getForce();

        for (int k=0; k<3; k++) {
            velocity.at(k) += this->dtHalf/atoms[i].getMass() * force.at(k) * velocity.at(k);
            position.at(k) += this->dt * velocity.at(k);
        }
        atoms[i].setVelocity(velocity);
        atoms[i].setPosition(position);

        /*atoms[i].setVelocity(atoms[i].getVelocity() + (this->dtHalf/atoms[i].getMass()) * atoms[i].getForce());
        atoms[i].setPosition(atoms[i].getPosition() + this->dt                          * atoms[i].getVelocity());*/
    }
    if (this->periodicBoundaryConditions) {
        this->system->applyPeriodicBoundaryConditions();
    }
    this->potential->computeForces(atoms, n);
    for (int i=0; i < n; i++) {
        velocity = atoms[i].getVelocity();
        force = atoms[i].getForce();

        for (int k=0; k<3; k++) {
            velocity.at(k) += this->dtHalf/atoms[i].getMass() * force.at(k);
        }
        atoms[i].setVelocity(velocity);

        //atoms[i].setVelocity(atoms[i].getVelocity() + (this->dtHalf/atoms[i].getMass()) * atoms[i].getForce());
    }
}

