#include "lennardjones.h"

using std::cout;
using std::endl;

LennardJones::LennardJones(double epsilon, double sigma, std::vector<double> systemSize) {
    this->epsilon = epsilon;
    this->sigma   = sigma;
    this->sigma6  = sigma*sigma*sigma*sigma*sigma*sigma;
    this->sigma12 = sigma6*sigma6;
    this->systemSize = systemSize;
}

void LennardJones::computeForces(std::vector<Atom*> atoms, int n) {

    Potential::setForcesToZero(atoms, n);
    this->potentialEnergy = 0;

    std::vector<double> dr{0,0,0};
    double r2 = 0;
    double f  = 0;
    double df = 0;

    for (int i=0; i < n; i++) {
        for (int j=i+1; j < n; j++) {
            r2 = 0;
            for (int k=0; k < 3; k++) {
                dr.at(k) = atoms.at(j)->getPosition().at(k) - atoms.at(i)->getPosition().at(k);
                if (dr.at(k) > this->systemSize.at(k) / 2.0) {
                    dr.at(k) = dr.at(k) - this->systemSize.at(k);
                } else if (dr.at(k) < -this->systemSize.at(k) / 2.0) {
                    dr.at(k) = dr.at(k) + this->systemSize.at(k);
                }
                r2 += dr.at(k)*dr.at(k);
            }
            r2  = 1.0 / r2;
            double r6  = r2*r2*r2;
            double r12 = r6*r6;
            double r8  = r6*r2; //r2*r2*r2*r2;
            double r14 = r8*r6; //r8*r2*r2*r2;
            this->potentialEnergy += 4*this->epsilon * (this->sigma12*r12-this->sigma6*r6);
            f = 24 * this->epsilon * (this->sigma6 * r8 - 2*this->sigma12 * r14);

            for (int k=0; k < 3; k++) {
                df = f * dr.at(k);
                atoms.at(i)->addForce( df, k);
                atoms.at(j)->addForce(-df, k);
            }
        }
    }
}

double LennardJones::computePotential(std::vector<Atom*> atoms, int n) {
    return this->potentialEnergy;
}


