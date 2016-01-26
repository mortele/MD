#include "potential.h"

Potential::Potential(System* system) {
    m_system = system;
}

void Potential::setForcesToZero(const std::vector<Atom*> & atoms, int n) {
    for (int i = 0; i < n; i++) {
        for (int k=0; k<3; k++) {
            atoms.at(i)->setForce(0, k);
        }
    }
}

