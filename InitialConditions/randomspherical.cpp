#include "randomspherical.h"


RandomSpherical::RandomSpherical(int n, double R0) {
    this->n  = n;
    this->R0 = R0;
}

void RandomSpherical::setupInitialCondition() {
    InitialCondition::n = this->n;
    this->atoms = new Atom[this->n];

    for (int i=0; i<this->n; i++) {
        double mass = Random::nextGaussian(10.0, 1.0);
        double x,y,z;
        double r = R0 + 1;
        while (r > R0) {
            x = (Random::nextDouble())*R0;
            y = (Random::nextDouble())*R0;
            z = (Random::nextDouble())*R0;
            r = std::sqrt( (x-R0/2.)*(x-R0/2.)
                          +(y-R0/2.)*(y-R0/2.)
                          +(z-R0/2.)*(z-R0/2.));
        }
        this->atoms[i].setMass(mass);
        this->atoms[i].setPosition(vec(x,y,z));
        this->atoms[i].setVelocity(vec());
    }

    InitialCondition::setupDone = true;
}



