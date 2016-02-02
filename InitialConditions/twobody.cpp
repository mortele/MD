#include "twobody.h"
#include <cmath>

TwoBody::TwoBody() {
    m_setupDone = false;
}

TwoBody::TwoBody(double e) {
    m_setupDone = false;
    m_e = e;
}

void TwoBody::setupInitialCondition() {
    m_n = 2;

    double earthMass = 0.5;
    std::vector<double> earthVelocity{0,2*std::acos(-1.0),0};
    std::vector<double> earthPosition{1+m_e,0,0};
    std::vector<double> sunVelocity{0,-2*std::acos(-1.0)/earthMass,0};
    std::vector<double> sunPosition{0,0,0};

    // Setup "sun."
    m_atoms.push_back(new Atom(1));
    m_atoms.at(0)->setMass(1.0);
    m_atoms.at(0)->setPosition(sunPosition);
    m_atoms.at(0)->setVelocity(sunVelocity);

    // Setup "earth."
    m_atoms.push_back(new Atom(1));
    m_atoms.at(1)->setMass(earthMass);
    m_atoms.at(1)->setPosition(earthPosition);
    m_atoms.at(1)->setVelocity(earthVelocity);

    m_setupDone = true;
}


