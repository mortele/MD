#include "lennardjones.h"

using std::cout;
using std::endl;

LennardJones::LennardJones(double epsilon,
                           double sigma,
                           std::vector<double> systemSize,
                           double rCut,
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
    double r2 = 1.0/m_rCut2;
    m_potentialAtCut = 4*m_epsilon * r2*r2*r2 * m_sigma6 * (m_sigma6 * r2*r2*r2 -1);
}

void LennardJones::computeForces(const std::vector<Atom*>& atoms, int n) {

    Potential::setForcesToZero(atoms, n);
    m_potentialEnergy = 0;

    std::vector<double> dr{0,0,0};
    double dr2 = 0;

    for (int i=0; i < n; i++) {
        for (int j=i+1; j < n; j++) {
            dr2 = 0;
            for (int k=0; k < 3; k++) {
                dr.at(k) = atoms.at(j)->getPosition().at(k) - atoms.at(i)->getPosition().at(k);
                if (dr.at(k) > m_systemSize.at(k) / 2.0) {
                    dr.at(k) = dr.at(k) - m_systemSize.at(k);
                } else if (dr.at(k) < -m_systemSize.at(k) / 2.0) {
                    dr.at(k) = dr.at(k) + m_systemSize.at(k);
                }
                dr2 += dr.at(k)*dr.at(k);
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
                const double df = f * dr.at(k);
                atoms.at(i)->addForce( df, k);
                atoms.at(j)->addForce(-df, k);
            }
        }
    }
}

double LennardJones::computePotential(const std::vector<Atom*>& atoms, int n) {
    return m_potentialEnergy;
}
