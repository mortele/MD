#include "uniform.h"

Uniform::Uniform(int n, std::vector<double> boxSize, double temperature) {
    m_setupDone = false;
    m_boxSize       = boxSize;
    m_n             = n;
    m_temperature   = temperature;
}

void Uniform::setupInitialCondition() {

    for (int i=0; i<m_n; i++) {
        double m = 1.0;
        m_atoms.push_back(new Atom(1));
        m_atoms.at(i)->setMass(m);

        for (int k=0; k<3; k++) {
            m_atoms.at(i)->setPosition(Random::nextDouble()*m_boxSize.at(k), k);
            m_atoms.at(i)->setVelocity(Random::nextGaussian(0, std::sqrt(m_temperature / m)), k);
        }
    }
    m_setupDone = true;
}

