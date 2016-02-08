#include "potential.h"
#include "../system.h"
#include "../vec.h"

Potential::Potential(System* system) {
    m_system = system;
}

void Potential::setForcesToZero() {
    for (int i = 0; i < m_system->getN(); i++) {
        Atom* atom = at(m_system->getAtoms(),i);
        for (int k=0; k<3; k++) {
            atom->setForce(0, k);
        }
    }
}

