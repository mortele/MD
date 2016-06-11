#include "initialcondition.h"
#include "../atom.h"

using std::cout;
using std::endl;

InitialCondition::InitialCondition() {
    m_setupDone = false;
}

void InitialCondition::removeLinearMomentum() {
    for (int k=0; k<3; k++) {
        m_totalMomentum.at(k) = 0;
    }
    for (int i=0; i<m_n; i++) {
        m_atoms.at(i)->setIndex(i);
        for (int k=0; k<3; k++) {
            m_totalMomentum.at(k) += m_atoms.at(i)->getVelocity().at(k) *
                                     m_atoms.at(i)->getMass();
        }
    }
    for (int k=0; k<3; k++) {
        m_totalMomentum.at(k) /= (real) m_n;
    }
    for (int i=0; i<m_n; i++) {
        for (int k=0; k<3; k++) {
            m_atoms.at(i)->addVelocity(-m_totalMomentum.at(k) /
                                       m_atoms.at(i)->getMass(), k);
        }
    }
}

void InitialCondition::generateTestMatrix(double poreRadius) {
    if (m_setupDone == false) {
        setupInitialCondition();
    }

    std::vector<real_posvel> pore{m_systemSize.at(0)/2.0,
                m_systemSize.at(1)/2.0,
                m_systemSize.at(2)/2.0};

    for (int i=0; i<m_n; i++) {
        Atom* atom = m_atoms.at(i);
        std::vector<real_posvel> position = atom->getPosition();
        double dr2 = 0;
        for (int k=0; k<3; k++) {
            double tmp = pore.at(k)-position.at(k);
            dr2 += tmp*tmp;
        }
        if (std::sqrt(dr2) < poreRadius) {
            m_atoms.at(i)->setIsMatrix(true);
            m_atoms.at(i)->setName("H");
            std::vector<real_posvel> velocity{0.0, 0.0, 0.0};
            m_atoms.at(i)->setVelocity(velocity);
        }
    }
}

void InitialCondition::generateMatrix() {

}



