#include "uniform.h"

Uniform::Uniform(int n, std::vector<double> boxSize, double temperature) {
    InitialCondition::setupDone = false;
    InitialCondition::n         = n;
    this->boxSize       = boxSize;
    this->n             = n;
    this->temperature   = temperature;
}

void Uniform::setupInitialCondition() {
    //this->atoms = new Atom[this->n];

    for (int i=0; i<this->n; i++) {
        //double m = atoms[i].getMass();
        double m = 1.0;
        this->atoms.push_back(new Atom());
        this->atoms.at(i)->setMass(m);

        for (int k=0; k<3; k++) {
            atoms.at(i)->setPosition(Random::nextDouble()*this->boxSize.at(k), k);
            atoms.at(i)->setVelocity(Random::nextGaussian(0, std::sqrt(this->temperature / m)), k);
        }
    }
    InitialCondition::setupDone = true;
}

