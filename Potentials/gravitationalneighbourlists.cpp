#include "gravitationalneighbourlists.h"
#include "../celllist.h"
#include "../neighbourlist.h"
#include "../system.h"

GravitationalNeighbourLists::GravitationalNeighbourLists(real G,
                                                         real eps,
                                                         real rCut,
                                                         real neighbourCut,
                                                         System* system) :
        Potential(system) {

    m_eps               = eps;
    m_systemSize        = system->getSystemSize();
    m_systemSizeHalf    = {m_systemSize[0]/2.0f, m_systemSize[1]/2.0f, m_systemSize[2]/2.0f};
    m_neighbourCut      = neighbourCut;
    m_neighbourCut2     = neighbourCut*neighbourCut;
    m_rCut              = rCut;
    m_rCut2             = rCut * rCut;
    m_neighbourList     = new NeighbourList(m_system, m_rCut, m_neighbourCut, m_systemSize);
    m_cellList          = m_neighbourList->getCellList();
    m_potentialAtCut    = - 1.0f / rCut;
}

void GravitationalNeighbourLists::computeForces() {
    if (m_timeStepsSinceLastCellListUpdate == -1 ||
        m_timeStepsSinceLastCellListUpdate >= 20) {
        m_timeStepsSinceLastCellListUpdate = 1;
        m_neighbourList->constructNeighbourLists();
    }
    m_timeStepsSinceLastCellListUpdate += 1;
    setForcesToZero();
    m_potentialEnergy       = 0;
    m_pressure              = 0;
    real dr2              = 0;
    real dr[3]            = {0,0,0};


    for (int i=0; i<m_system->getN(); i++) {
        Atom* atom1 = at(m_system->getAtoms(), i);
        vector<Atom*> neighbours = m_neighbourList->getNeighbours(atom1->getIndex());

        for (unsigned int j=0; j<neighbours.size(); j++) {
            Atom* atom2 = at(neighbours, j);

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

            if (atom1 != atom2) {
                const real r2         = 1.0f / dr2;
                const int cut         = (dr2 < m_rCut2);
                const real f          = - r2 * cut;
                //m_potentialEnergy     += - std::sqrt(r2) * cut;

                for (int k=0; k < 3; k++) {
                    const real df = f * dr[k];
                    atom1->addForce(-df, k);
                    atom2->addForce( df, k);
                    //m_pressure += f * std::sqrt(dr2) * r2;
                }
            }
        }
    }
}

real GravitationalNeighbourLists::computePotential() {
    //return m_potentialEnergy;
    return 0;
}
