#include "lennardjones.h"
#include "../atom.h"
#include "../vec.h"
#include "../system.h"

using std::cout;
using std::endl;

LennardJones::LennardJones(real epsilon,
                           real sigma,
                           std::vector<real> systemSize,
                           real rCut,
                           System* system) :
        Potential(system) {
    m_epsilon = epsilon;
    m_24epsilon = 24*epsilon;
    m_sigma   = sigma;
    m_sigma6  = sigma*sigma*sigma*sigma*sigma*sigma;
    m_sigma12 = m_sigma6*m_sigma6;
    m_4epsilonSigma6 = 4*epsilon*m_sigma6;
    m_rCut = rCut;
    m_rCut2 = rCut*rCut;
    m_systemSize = systemSize;
    real r2 = 1.0/m_rCut2;
    m_potentialAtCut = 4*m_epsilon * r2*r2*r2 * m_sigma6 * (m_sigma6 * r2*r2*r2 -1);
}

void LennardJones::computeForces() {

    Potential::setForcesToZero();
    m_potentialEnergy = 0;

    std::vector<real> dr{0,0,0};
    real dr2 = 0;

    for (int i=0; i < m_system->getN(); i++) {
        Atom* atomi = at(m_system->getAtoms(),i);
        for (int j=i+1; j < m_system->getN(); j++) {
            Atom* atomj = at(m_system->getAtoms(), j);
            dr2 = 0;
            for (int k=0; k < 3; k++) {
                at(dr,k) = at(atomj->getPosition(),k) - at(atomi->getPosition(),k);
                if (at(dr,k) > at(m_systemSize,k)*0.5) {
                    at(dr,k) = at(dr,k) - at(m_systemSize,k);
                } else if (at(dr,k) < -at(m_systemSize,k)*0.5) {
                    at(dr,k) = at(dr,k) + at(m_systemSize,k);
                }
                dr2 += at(dr,k)*at(dr,k);
            }
            const real r2         = 1.0f / dr2;
            const real r6         = r2*r2*r2;
            const real sigma6r6   = m_sigma6 * r6;
            const int cut           = (dr2 < m_rCut2);
            const real f          = -m_24epsilon * sigma6r6 *
                                      (2*sigma6r6 - 1) * r2 * cut;
            m_potentialEnergy      += (m_4epsilonSigma6 * r6 *
                                       (sigma6r6 - 1) - m_potentialAtCut) * cut;
            for (int k=0; k < 3; k++) {
                const real df = f * dr.at(k);
                atomi->addForce( df, k);
                atomj->addForce(-df, k);
            }
        }
    }
}

real LennardJones::computePotential() {
    return m_potentialEnergy;
}
