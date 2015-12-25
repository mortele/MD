#include "gravitational.h"

Gravitational::Gravitational(double G) {
    this->G = G;
}


void Gravitational::computeForces(Atom* atoms, int n) {

    Potential::setForcesToZero(atoms, n);


    for (int i=0; i < n; i++) {
        for (int j=0; j < n; j++) {
            if (i != j) {
                double r2 = atoms[i].getPosition().
                            computeLengthSquared(atoms[j].getPosition()) + 0.1;

                vec posi = atoms[i].getPosition();
                vec posj = atoms[j].getPosition();

                double dx = posi[0]-posj[0];
                double dy = posi[1]-posj[1];
                double dz = posi[2]-posj[2];

                double f = - this->G * atoms[i].getMass() * atoms[j].getMass() / r2;

                vec dforce = vec(f*dx, f*dy, f*dz);
                atoms[i].addForce(dforce);
            }
        }
    }
}
