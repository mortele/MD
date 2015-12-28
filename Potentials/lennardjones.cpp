#include "lennardjones.h"

LennardJones::LennardJones(double epsilon, double sigma) {
    this->epsilon = epsilon;
    this->sigma   = sigma;
    this->sigma6  = sigma*sigma*sigma*sigma*sigma*sigma;
    this->sigma12 = sigma6*sigma6;
}

void LennardJones::computeForces(Atom* atoms, int n) {

    Potential::setForcesToZero(atoms, n);

    for (int i=0; i < n; i++) {
        for (int j=0; j < n; j++) {
            if (i != j) {
                double r2 = atoms[i].getPosition().
                           computeLengthSquared(atoms[j].getPosition());
                r2  = 1.0 / r2;
                double r8  = r2*r2*r2*r2;
                double r14 = r8*r2*r2*r2;

                vec posi = atoms[i].getPosition();
                vec posj = atoms[j].getPosition();

                double dx = posi[0]-posj[0];
                double dy = posi[1]-posj[1];
                double dz = posi[2]-posj[2];

                double f = 4*this->epsilon * (this->sigma6 * r8 -
                                              this->sigma12 * r14);

                vec dforce = vec(f*dx, f*dy, f*dz);
                atoms[i].addForce(dforce);
            }
        }
    }
}


