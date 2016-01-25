#include "potential.h"

Potential::Potential() {

}

void Potential::setForcesToZero(Atom* atoms, int n) {
    std::vector<double> force{0,0,0};

    for (int i = 0; i < n; i++) {
        force = atoms[i].getForce();

        for (int k=0; k<3; k++) {
            force.at(k) = 0;
        }
        atoms[i].setForce(force);

        //atoms[i].setForce(vec());
    }
}

