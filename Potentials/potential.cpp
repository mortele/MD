#include "potential.h"

Potential::Potential() {

}

void Potential::setForcesToZero(Atom* atoms, int n) {
    for (int i = 0; i < n; i++) {
        for (int k=0; k<3; k++) {
            atoms[i].setForce(0, k);
        }
    }
}

