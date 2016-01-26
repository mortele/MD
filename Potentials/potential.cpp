#include "potential.h"

Potential::Potential(System* system) {
    this->system = system;
}

void Potential::setForcesToZero(std::vector<Atom*> atoms, int n) {
    for (int i = 0; i < n; i++) {
        for (int k=0; k<3; k++) {
            atoms.at(i)->setForce(0, k);
        }
    }
}

