#include "uniform.h"

Uniform::Uniform(int n, std::vector<double> boxSize, double temperature) {
    InitialCondition::setupDone = false;
    InitialCondition::n         = n;
    this->boxSize       = boxSize;
    this->n             = n;
    this->temperature   = temperature;
}

void Uniform::setupInitialCondition() {
    this->atoms = new Atom[this->n];

    for (int i=0; i<this->n; i++) {
        /*vec position = vec();
        vec velocity = vec();*/
        double m = atoms[i].getMass();

        std::vector<double> position{0,0,0};
        std::vector<double> velocity{0,0,0};

        for (int k=0; k<3; k++) {
            position.at(k) = Random::nextDouble()*this->boxSize.at(k);
            velocity.at(k) = Random::nextGaussian(0, std::sqrt(this->temperature / m));

            /*position.set(x, j);
            velocity.set(v, j);*/
        }
        atoms[i].setPosition(position);
        atoms[i].setVelocity(velocity);

        /*atoms[i].setPosition(position);
        atoms[i].setVelocity(velocity);*/
    }
    InitialCondition::setupDone = true;
}

