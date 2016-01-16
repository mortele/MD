#include "lennardjones.h"

using std::cout;
using std::endl;

LennardJones::LennardJones(double epsilon, double sigma, vec systemSize) {
    this->epsilon = epsilon;
    this->sigma   = sigma;
    this->sigma6  = sigma*sigma*sigma*sigma*sigma*sigma;
    this->sigma12 = sigma6*sigma6;
    this->systemSize = systemSize;
}

void LennardJones::computeForces(Atom* atoms, int n) {

    Potential::setForcesToZero(atoms, n);
    this->potentialEnergy = 0;

    for (int i=0; i < n; i++) {
        for (int j=i+1; j < n; j++) {
            vec dr = vec::computeLength(atoms[j].getPosition(),
                                        atoms[i].getPosition(),
                                        this->systemSize);

            double r2 = dr.computeLengthSquared();

            r2  = 1.0 / r2;
            double r6  = r2*r2*r2;
            double r12 = r6*r6;
            double r8  = r6*r2; //r2*r2*r2*r2;
            double r14 = r8*r6; //r8*r2*r2*r2;

            this->potentialEnergy += 4*this->epsilon * (this->sigma12*r12-this->sigma6*r6);
            double f = 24 * this->epsilon * (  this->sigma6  * r8 -
                                             2*this->sigma12 * r14);

            vec dforce      = vec(f*dr[0], f*dr[1], f*dr[2]);
            vec dforceMinus = vec(-f*dr[0], -f*dr[1], -f*dr[2]);
            atoms[i].addForce(dforce);
            atoms[j].addForce(dforceMinus);

        }
    }
}

double LennardJones::computePotential(Atom* atoms, int n) {
    return this->potentialEnergy;
}


