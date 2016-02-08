#include "velocityverlet.h"
#include <vector>
#include <iostream>
#include "../Potentials/potential.h"
#include "../system.h"
#include "../vec.h"

using std::cout;
using std::endl;

VelocityVerlet::VelocityVerlet(real dt, System* system) :
        Integrator(dt, system) {
    m_firstStep = true;
    m_dtHalf = dt/2.0;
}

void VelocityVerlet::advance() {
    if (m_firstStep) {
        m_potential->computeForces();
        m_firstStep = false;
        m_periodicBoundaryConditions = m_system->getPeriodicBoundaryConditions();
    }
    for (int i=0; i < m_system->getN(); i++) {
        Atom* atom = at(m_system->getAtoms(), i);
        for (int k=0; k<3; k++) {
            atom->addVelocity(m_dtHalf/atom->getMass() * at(atom->getForce(),k), k);
            atom->addPosition(m_dt * at(atom->getVelocity(),k), k);
        }
    }
    if (m_periodicBoundaryConditions) {
        m_system->applyPeriodicBoundaryConditions();
    }
    m_potential->computeForces();
    for (int i=0; i < m_system->getN(); i++) {
        Atom* atom = at(m_system->getAtoms(),i);
        for (int k=0; k<3; k++) {
            atom->addVelocity(m_dtHalf/atom->getMass() * at(atom->getForce(),k), k);
        }
    }
}

