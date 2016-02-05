#include "velocityverlet.h"
#include <vector>
#include <iostream>
#include "../Potentials/potential.h"
#include "../system.h"
#include "../vec.h"

using std::cout;
using std::endl;

VelocityVerlet::VelocityVerlet(real dt, System* system) :
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
            atoms[i]->addVelocity(m_dtHalf/atoms[i]->getMass() * at(atoms[i]->getForce(),k), k);
            atoms[i]->addPosition(m_dt * at(atoms[i]->getVelocity(),k), k);
        }
    }
    if (m_periodicBoundaryConditions) {
        m_system->applyPeriodicBoundaryConditions();
    }
    m_potential->computeForces(atoms, n);
    for (int i=0; i < n; i++) {
        for (int k=0; k<3; k++) {
            atoms[i]->addVelocity(m_dtHalf/atoms[i]->getMass() * at(atoms[i]->getForce(),k), k);
        }
    }
}

