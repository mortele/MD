#include "gravitational.h"

using std::endl;
using std::cout;

Gravitational::Gravitational(double G) {
    this->G     = G;
    this->eps   = 0;
}

Gravitational::Gravitational(double G, double eps) {
    this->G     = G;
    this->eps   = eps;
}


void Gravitational::computeForces(Atom* atoms, int n) {

    Potential::setForcesToZero(atoms, n);

    for (int i=0; i < n; i++) {
        for (int j=0; j < n; j++) {
            if (i != j) {
                double r2 = atoms[i].getPosition().
                            computeLengthSquared(atoms[j].getPosition());

                vec posi = atoms[i].getPosition();
                vec posj = atoms[j].getPosition();

                double dx = posi[0]-posj[0];
                double dy = posi[1]-posj[1];
                double dz = posi[2]-posj[2];

                double f = - this->G * atoms[i].getMass() * atoms[j].getMass() / (r2+this->eps);

                vec dforce = vec(f*dx, f*dy, f*dz);
                atoms[i].addForce(dforce);
            }
        }
    }
}

double Gravitational::computePotential(Atom* atoms, int n) {
    double potentialEnergy = 0;

    for (int i=0; i < n; i++) {
        for (int j=0; j < n; j++) {
            if (i != j) {
                double r = std::sqrt(atoms[i].getPosition().
                                     computeLengthSquared(atoms[j].getPosition()));

                potentialEnergy -= this->G * atoms[i].getMass() * atoms[j].getMass() / r;
            }
        }
    }

    return potentialEnergy / 2.0;
}







