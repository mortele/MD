#include "velocityverlet.h"
#include <vector>
#include <iostream>
#include "../Potentials/potential.h"
#include "../system.h"

using std::cout;
using std::endl;

VelocityVerlet::VelocityVerlet(double dt, System* system) :
        Integrator(dt) {
    m_firstStep = true;
    m_dtHalf = dt/2.0;
    m_system = system;
}

void VelocityVerlet::advance(const std::vector<Atom*> & atoms, int n) {
    if (m_firstStep) {
        m_potential->computeForces(atoms, n);
        m_firstStep = false;
        m_periodicBoundaryConditions = m_system->getPeriodicBoundaryConditions();
    }
    for (int i=0; i < n; i++) {
        for (int k=0; k<3; k++) {
            atoms.at(i)->addVelocity(m_dtHalf/atoms.at(i)->getMass() * atoms.at(i)->getForce().at(k), k);
            atoms.at(i)->addPosition(m_dt * atoms.at(i)->getVelocity().at(k), k);
        }
    }
    if (m_periodicBoundaryConditions) {
        m_system->applyPeriodicBoundaryConditions();
    }
    m_potential->computeForces(atoms, n);
    for (int i=0; i < n; i++) {
        for (int k=0; k<3; k++) {
            atoms.at(i)->addVelocity(m_dtHalf/atoms.at(i)->getMass() * atoms.at(i)->getForce().at(k), k);
        }
    }
}

