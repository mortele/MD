#include "potential.h"

Potential::Potential() {

}

double Potential::computePotential(Atom* atoms, int n) {
    return 0;
}

void Potential::setForcesToZero(Atom* atoms, int n) {
    for (int i = 0; i < n; i++) {
        atoms[i].setForce(vec());
    }
}

