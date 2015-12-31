#include "twobody.h"
#include <cmath>

TwoBody::TwoBody() {
    InitialCondition::setupDone = false;
}

TwoBody::TwoBody(double e) {
    this->e = e;
}

void TwoBody::setupInitialCondition() {
    InitialCondition::n = 2;
    this->atoms = new Atom[InitialCondition::n];

    // Setup "earth."
    double earthVelocity = 2*std::acos(-1.0);
    //atoms[1].setMass(std::pow(10.0,-6));
    atoms[1].setMass(0.5);
    atoms[1].setPosition(vec(1+this->e,0,0));
    atoms[1].setVelocity(vec(0,earthVelocity,0));

    // Setup "sun."
    atoms[0].setMass(1.0);
    atoms[0].setPosition(vec());
    atoms[0].setVelocity(vec(0,-std::pow(10.0,-6)*earthVelocity,0));

    InitialCondition::setupDone = true;
}

/*Atom*TwoBody::getAtoms() {
    if (InitialCondition::setupDone == false) {
        this->setupInitialCondition();
    }
    return this->atoms;
}*/



