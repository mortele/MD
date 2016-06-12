#include "initialcondition.h"
#include "../atom.h"
#include "../random.h"

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
        std::vector<real_posvel> dr{0, 0, 0};
        double dr2 = 0;
        for (int k=0; k<3; k++) {
            at(dr,k) = at(atom->getPosition(),k) - at(pore,k);
            if (at(dr,k) > at(m_systemSize,k)*0.5) {
                at(dr,k) = at(dr,k) - at(m_systemSize,k);
            } else if (at(dr,k) < -at(m_systemSize,k)*0.5) {
                at(dr,k) = at(dr,k) + at(m_systemSize,k);
            }
            dr2 += at(dr,k)*at(dr,k);
        }
        if (std::sqrt(dr2) > poreRadius) {
            m_atoms.at(i)->setIsMatrix(true);
            m_atoms.at(i)->setName("H");
            std::vector<real_posvel> velocity{0.0, 0.0, 0.0};
            m_atoms.at(i)->setVelocity(velocity);
        }
    }
}

void InitialCondition::generateMatrix(double lowerRadius,
                                      double upperRadius,
                                      int    numberOfPores) {
    if (m_setupDone == false) {
        setupInitialCondition();
    }

    for (int i=0; i<m_n; i++) {
        Atom* atom = m_atoms.at(i);
        atom->setIsMatrix(true);
        atom->setName("Ne");
    }

    for (int p=0; p<numberOfPores; p++) {
        std::vector<real_posvel> pore{0,0,0};
        for (int k=0; k<3; k++) {
            pore.at(k) = Random::nextReal()*m_systemSize.at(k);
        }

        for (int i=0; i<m_n; i++) {
            Atom* atom = m_atoms.at(i);
            std::vector<real_posvel> position = atom->getPosition();
            std::vector<real_posvel> dr{0, 0, 0};
            double dr2 = 0;
            for (int k=0; k<3; k++) {
                at(dr,k) = at(atom->getPosition(),k) - at(pore,k);
                if (at(dr,k) > at(m_systemSize,k)*0.5) {
                    at(dr,k) = at(dr,k) - at(m_systemSize,k);
                } else if (at(dr,k) < -at(m_systemSize,k)*0.5) {
                    at(dr,k) = at(dr,k) + at(m_systemSize,k);
                }
                dr2 += at(dr,k)*at(dr,k);
            }
            double poreRadius = Random::nextReal()*(upperRadius-lowerRadius)+lowerRadius;
            if (std::sqrt(dr2) < poreRadius) {
                m_atoms.at(i)->setIsMatrix(false);
                m_atoms.at(i)->setName("Ar");
            }
        }
    }
    for (int i=0; i<m_n; i++) {
        Atom* atom = m_atoms.at(i);
        if (atom->getIsMatrix()) {
            std::vector<real_posvel> velocity{0.0, 0.0, 0.0};
            m_atoms.at(i)->setVelocity(velocity);
        }
    }
}



