#include "lennardjones.h"
#include "../celllist.h"
#include "../system.h"

using std::cout;
using std::endl;

LennardJones::LennardJones(std::vector<double>  systemSize,
                           double               rCut,
                           System*              system) :
    LennardJones(1.0, 3.405, systemSize, rCut, system) {
}

LennardJones::LennardJones(double               epsilon,
                           double               sigma,
                           std::vector<double>  systemSize,
                           double               rCut,
                           System*              system) :
    Potential(system) {

    m_epsilon           = epsilon;
    m_sigma             = sigma;
    m_sigma6            = sigma*sigma*sigma*sigma*sigma*sigma;
    m_24epsilonSigma6   = 24*m_epsilon*m_sigma6;
    m_4epsilonSigma6    = 4*m_epsilon*m_sigma6;
    m_systemSize        = systemSize;
    m_systemSizeHalf    = {systemSize[0]/2.0, systemSize[1]/2.0, systemSize[2]/2.0};
    m_rCut              = rCut;
    m_rCut2             = rCut * rCut;
    m_cellList          = new CellList(m_system, m_rCut);
    double r2           = 1.0 / m_rCut2;
    m_potentialAtCut    = 4*m_epsilon * r2*r2*r2 * m_sigma6 * (m_sigma6*r2-1);
}

void LennardJones::computeForces(const std::vector<Atom*> & atoms, int n) {

    if (m_timeStepsSinceLastCellListUpdate == -1 ||
        m_timeStepsSinceLastCellListUpdate >= 2) {
        m_timeStepsSinceLastCellListUpdate = 0;
        m_cellList->updateCellLists();
    }
    m_timeStepsSinceLastCellListUpdate += 1;
    setForcesToZero(atoms, n);
    m_potentialEnergy       = 0;
    m_pressure              = 0;
    double dr2              = 0;
    double df               = 0;
    double dr[3]            = {0,0,0};

    const int numberOfCellsInEachDirection = m_cellList->getNumberOfCellsInEachDirection();
    for (int ci=0; ci<numberOfCellsInEachDirection; ci++) {
    for (int cj=0; cj<numberOfCellsInEachDirection; cj++) {
    for (int ck=0; ck<numberOfCellsInEachDirection; ck++) {
        const int index1 = m_cellList->projectFromCellCoordinatesToIndex(ci,cj,ck);

        for (int di=0; di <= 1; di++) {
        for (int dj=(di==0 ? 0 : -1); dj <= 1; dj++) {
        for (int dk=(di==0 && dj==0 ? 0 : -1); dk <= 1; dk++) {
            const int index2 = m_cellList->projectFromCellCoordinatesToIndexPeriodic(ci+di, cj+dj, ck+dk);

            for (int i=0; i<m_cellList->getSizeOfCellList(index1); i++) {
                for (int j=0; j<m_cellList->getSizeOfCellList(index2); j++) {

                    Atom* atom1 = at(m_cellList->getCell(index1),i);
                    Atom* atom2 = at(m_cellList->getCell(index2),j);

                    dr2 = 0;
                    for (int k=0; k < 3; k++) {
                        dr[k] = at(atom1->getPosition(),k) - at(atom2->getPosition(),k);
                        if (dr[k] > at(m_systemSizeHalf,k)) {
                            dr[k] = dr[k] - at(m_systemSize,k);
                        } else if (dr[k] < -at(m_systemSizeHalf,k)) {
                            dr[k] = dr[k] + at(m_systemSize,k);
                        }
                        dr2 += dr[k]*dr[k];
                    }
                    if (!(index1==index2 && i == j)) {
                        const double r2  = 1.0 / dr2;
                        const double r6 = r2*r2*r2;
                        const double sigma6r6 = m_sigma6 * r6;
                        const double f  = -24*m_epsilon * sigma6r6 *
                                          (2*sigma6r6 - 1) * r2 * (dr2 < m_rCut2);
                        m_potentialEnergy += (m_4epsilonSigma6 * r6 *
                                             (sigma6r6 - 1) - m_potentialAtCut) *  (dr2 < m_rCut2);;

                        for (int k=0; k < 3; k++) {
                            df = f * dr[k];
                            atom1->addForce(-df, k);
                            atom2->addForce( df, k);
                            //m_pressure += f * std::sqrt(dr2) * r2;
                        }
                    }
                }
            }
        }}}
    }}}
}




double LennardJones::computePotential(const std::vector<Atom*> & atoms, int n) {
    return m_potentialEnergy;
}


