#include "twobody.h"
#include <cmath>

TwoBody::TwoBody() {
    InitialCondition::setupDone = false;
}

TwoBody::TwoBody(double e) {
    InitialCondition::setupDone = false;
    this->e = e;
}

void TwoBody::setupInitialCondition() {
    InitialCondition::n = 2;
    this->atoms = new Atom[InitialCondition::n];

    double earthMass = 0.5;
    std::vector<double> earthVelocity{0,2*std::acos(-1.0),0};
    std::vector<double> earthPosition{1+this->e,0,0};
    std::vector<double> sunVelocity{0,-2*std::acos(-1.0)/earthMass,0};
    std::vector<double> sunPosition{0,0,0};

    // Setup "earth."
    atoms[1].setMass(earthMass);
    atoms[1].setPosition(earthPosition);
    atoms[1].setVelocity(earthVelocity);

    // Setup "sun."
    atoms[0].setMass(1.0);
    atoms[0].setPosition(sunPosition);
    atoms[0].setVelocity(sunVelocity);

    InitialCondition::setupDone = true;
}


