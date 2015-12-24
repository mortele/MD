#include "potential.h"

Potential::Potential() {

}

void Potential::setForcesToZero(Atom* atoms, int n) {
    for (int i = 0; i < n; i++) {
        atoms[i].setForce(vec());
    }
}

