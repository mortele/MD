#include "twobody.h"
#include <tgmath.h>

TwoBody::TwoBody() {
    m_setupDone = false;
}

TwoBody::TwoBody(real e) {
    m_setupDone = false;
    m_e = e;
}

void TwoBody::setupInitialCondition() {
    m_n = 2;

    real earthMass = 0.5;
    std::vector<real_posvel> earthVelocity{0,2*std::acos(-1.0f),0};
    std::vector<real_posvel> earthPosition{1+m_e,0,0};
    std::vector<real_posvel> sunVelocity{0,-2*std::acos(-1.0f)/earthMass,0};
    std::vector<real_posvel> sunPosition{0,0,0};

    // Setup "sun."
    m_atoms.push_back(new Atom(1));
    m_atoms.at(0)->setMass(1.0f);
    m_atoms.at(0)->setPosition(sunPosition);
    m_atoms.at(0)->setVelocity(sunVelocity);

    // Setup "earth."
    m_atoms.push_back(new Atom(1));
    m_atoms.at(1)->setMass(earthMass);
    m_atoms.at(1)->setPosition(earthPosition);
    m_atoms.at(1)->setVelocity(earthVelocity);

    m_setupDone = true;
}


