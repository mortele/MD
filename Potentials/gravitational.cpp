#include "gravitational.h"
#include <vector>

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

    std::vector<double> dr{0,0,0};
    std::vector<double> dForce{0,0,0};
    std::vector<double> dForceMinus{0,0,0};
    double r  = 0;
    double r2 = 0;
    double f  = 0;
    this->potentialEnergy = 0;

    for (int i=0; i < n; i++) {
        for (int j=i+1; j < n; j++) {

                r2 = 0;
                for (int k=0; k < 3; k++) {
                    dr.at(k) = atoms[j].getPosition().at(k) -
                               atoms[i].getPosition().at(k);
                    r2      += dr.at(k)*dr.at(k);
                }

                f = -this->G * atoms[i].getMass() * atoms[j].getMass() /
                    (r2 + this->eps);

                for (int k=0; k<3; k++) {
                    dForce.at(k) = f * dr.at(k);
                    dForceMinus.at(k) = -dForce.at(k);
                }
                atoms[i].setForce(dForce);
                atoms[j].setForce(dForceMinus);

                this->potentialEnergy += - std::sqrt(r2) * f;

                /*double r2 = atoms[i].getPosition().
                            computeLengthSquared(atoms[j].getPosition());

                vec posi = atoms[i].getPosition();
                vec posj = atoms[j].getPosition();

                double dx = posi[0]-posj[0];
                double dy = posi[1]-posj[1];
                double dz = posi[2]-posj[2];

                double f = - this->G * atoms[i].getMass() * atoms[j].getMass() / (r2+this->eps);

                vec dforce = vec(f*dx, f*dy, f*dz);
                atoms[i].addForce(dforce);*/
        }
    }
}

double Gravitational::computePotential(Atom* atoms, int n) {
    /*double potentialEnergy = 0;

    for (int i=0; i < n; i++) {
        for (int j=0; j < n; j++) {
            if (i != j) {
                double r = std::sqrt(atoms[i].getPosition().
                                     computeLengthSquared(atoms[j].getPosition()));

                potentialEnergy -= this->G * atoms[i].getMass() * atoms[j].getMass() / r;
            }
        }
    }

    return potentialEnergy / 2.0;*/
    return this->potentialEnergy;
}







