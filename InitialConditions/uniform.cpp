#include "uniform.h"

Uniform::Uniform(int n, vec boxSize, double temperature) {
    InitialCondition::setupDone = false;
    InitialCondition::n         = n;
    this->boxSize       = boxSize;
    this->n             = n;
    this->temperature   = temperature;
}

void Uniform::setupInitialCondition() {
    this->atoms = new Atom[this->n];

    for (int i=0; i<this->n; i++) {
        vec position = vec();
        vec velocity = vec();
        double m = atoms[i].getMass();

        for (int j=0; j<3; j++) {
            double x = Random::nextDouble()*this->boxSize[j];
            double v = Random::nextGaussian(0, std::sqrt(this->temperature / m));
            position.set(x, j);
            velocity.set(v, j);
        }
        atoms[i].setPosition(position);
        atoms[i].setVelocity(velocity);
    }
    InitialCondition::setupDone = true;
}

