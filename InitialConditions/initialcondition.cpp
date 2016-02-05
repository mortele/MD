#include "initialcondition.h"
#include "../atom.h"

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



