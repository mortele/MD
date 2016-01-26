#include "lennardjones.h"
#include "../celllist.h"
#include "../system.h"

using std::cout;
using std::endl;

LennardJones::LennardJones(double epsilon,
                           double sigma,
                           std::vector<double> systemSize,
                           double rCut,
                           System* system) :
        Potential(system) {
    m_epsilon = epsilon;
    m_sigma   = sigma;
    m_sigma6  = sigma*sigma*sigma*sigma*sigma*sigma;
    m_24epsilonSigma6 = 24*m_epsilon*m_sigma6;
    m_4epsilonSigma6 = 4*m_epsilon*m_sigma6;
    m_systemSize = systemSize;
    m_rCut  = rCut;
    m_rCut2 = rCut * rCut;
    m_cellList = new CellList(m_system, m_rCut);
    double r2 = 1.0 / m_rCut2;
    m_potentialAtCut = 4*m_epsilon * r2*r2*r2 * m_sigma6 * (m_sigma6*r2-1);
}

void LennardJones::computeForces(const std::vector<Atom*> & atoms, int n) {

    if (m_timeStepsSinceLastCellListUpdate == -1 ||
        m_timeStepsSinceLastCellListUpdate >= 10) {
        m_cellList->computeCellLists(atoms, n);
    }
    m_timeStepsSinceLastCellListUpdate += 1;
    setForcesToZero(atoms, n);
    m_potentialEnergy       = 0;
    m_pressure              = 0;
    double dr2              = 0;
    double df               = 0;
    bool   compute          = false;
    std::vector<double> dr{0,0,0};

    for (int i=0; i < n; i++) {
        for (int j=0; j < n; j++) {
            compute = (i != j) * m_cellList->isNeighbour(atoms.at(i)->getCellListIndex(),
                                                         atoms.at(j)->getCellListIndex());

            if (compute) {
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

                const double r2  = 1.0 / dr2;
                const double r6 = r2*r2*r2;
                const double sigma6r6 = m_sigma6 * r6;
                const double f  = -24*m_epsilon * sigma6r6 *
                                  (2*sigma6r6 - 1) * r2 * (dr2 < m_rCut2);
                m_potentialEnergy += m_4epsilonSigma6 * r6 *
                                     (sigma6r6 - 1) - m_potentialAtCut;

                for (int k=0; k < 3; k++) {
                    df = f * dr.at(k);
                    atoms.at(i)->addForce( df, k);
                    atoms.at(j)->addForce(-df, k);
                    m_pressure -= f * std::sqrt(dr2) * r2;
                }
            }
        }
    }
}

double LennardJones::computePotential(const std::vector<Atom*> & atoms, int n) {
    return m_potentialEnergy;
}


