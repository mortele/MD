#include "lennardjonescelllists.h"
#include "../celllist.h"
#include "../system.h"

using std::cout;
using std::endl;

LennardJonesCellLists::LennardJonesCellLists(   std::vector<real>  systemSize,
                                                real               rCut,
                                                System*              system) :
    LennardJonesCellLists(1.0, 3.405, systemSize, rCut, system) {
}

LennardJonesCellLists::LennardJonesCellLists(   real               epsilon,
                                                real               sigma,
                                                std::vector<real>  systemSize,
                                                real               rCut,
                                                System*              system) :
    Potential(system) {

    m_epsilon           = epsilon;
    m_sigma             = sigma;
    m_sigma6            = sigma*sigma*sigma*sigma*sigma*sigma;
    m_24epsilon         = 24*m_epsilon;
    m_4epsilonSigma6    = 4*m_epsilon*m_sigma6;
    m_systemSize        = systemSize;
    m_systemSizeHalf    = {systemSize[0]/2.0f, systemSize[1]/2.0f, systemSize[2]/2.0f};
    m_rCut              = rCut;
    m_rCut2             = rCut * rCut;
    m_cellList          = new CellList(m_system, m_rCut);
    real r2           = 1.0 / m_rCut2;
    m_potentialAtCut    = 4*m_epsilon * r2*r2*r2 * m_sigma6 * (m_sigma6*r2*r2*r2-1);
}

void LennardJonesCellLists::computeForces() {

    if (m_timeStepsSinceLastCellListUpdate == -1 ||
        m_timeStepsSinceLastCellListUpdate >= 20) {
        m_timeStepsSinceLastCellListUpdate = 1;
        m_cellList->updateCellLists();
    }
    m_timeStepsSinceLastCellListUpdate += 1;
    setForcesToZero();
    m_potentialEnergy       = 0;
    m_pressure              = 0;
    real dr2              = 0;
    real df               = 0;
    real dr[3]            = {0,0,0};

    const int numberOfCellsInEachDirection = m_cellList->getNumberOfCellsInEachDirection();
    for (int ci=0; ci<numberOfCellsInEachDirection; ci++) {
    for (int cj=0; cj<numberOfCellsInEachDirection; cj++) {
    for (int ck=0; ck<numberOfCellsInEachDirection; ck++) {

        for (int di=0; di <= 1; di++) {
        for (int dj=(di==0 ? 0 : -1); dj <= 1; dj++) {
        for (int dk=(di==0 && dj==0 ? 0 : -1); dk <= 1; dk++) {

            const int cii = (ci+di==-1 ? numberOfCellsInEachDirection-1 : (ci+di==numberOfCellsInEachDirection ? 0 : ci+di));
            const int cjj = (cj+dj==-1 ? numberOfCellsInEachDirection-1 : (cj+dj==numberOfCellsInEachDirection ? 0 : cj+dj));
            const int ckk = (ck+dk==-1 ? numberOfCellsInEachDirection-1 : (ck+dk==numberOfCellsInEachDirection ? 0 : ck+dk));

            for (int i=0; i<m_cellList->getSizeOfCellList(ci,  cj, ck);   i++) {
            for (int j=(di==0 && dj==0 && dk==0)*(i+1); j<m_cellList->getSizeOfCellList(cii, cjj, ckk); j++) {

                Atom* atom1 = at(m_cellList->getCell(ci,  cj,  ck),  i);
                Atom* atom2 = at(m_cellList->getCell(cii, cjj, ckk), j);

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

                const real r2         = 1.0 / dr2;
                const real r6         = r2*r2*r2;
                const real sigma6r6   = m_sigma6 * r6;
                const int cut           = (dr2 < m_rCut2);
                const real f          = -m_24epsilon * sigma6r6 *
                                          (2*sigma6r6 - 1) * r2 * cut;
                m_potentialEnergy      += (m_4epsilonSigma6 * r6 *
                                           (sigma6r6 - 1) - m_potentialAtCut) * cut;

                for (int k=0; k < 3; k++) {
                    df = f * dr[k];
                    atom1->addForce(-df, k);
                    atom2->addForce( df, k);
                    //m_pressure += f * std::sqrt(dr2) * r2;
                }
            }}
        }}}
    }}}
}




real LennardJonesCellLists::computePotential() {
    return m_potentialEnergy;
}
