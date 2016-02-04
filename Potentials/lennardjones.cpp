#include "lennardjones.h"
#include "../celllist.h"
#include "../neighbourlist.h"
#include "../system.h"

using std::cout;
using std::endl;

LennardJones::LennardJones(std::vector<double>  systemSize,
                           double               rCut,
                           System*              system) :
    LennardJones(1.0, 3.405, systemSize, rCut, rCut, system) {
}

LennardJones::LennardJones(double               epsilon,
                           double               sigma,
                           std::vector<double>  systemSize,
                           double               rCut,
                           double               neighbourCut,
                           System*              system) :
    Potential(system) {

    m_epsilon           = epsilon;
    m_sigma             = sigma;
    m_sigma6            = sigma*sigma*sigma*sigma*sigma*sigma;
    m_24epsilon         = 24*m_epsilon;
    m_4epsilonSigma6    = 4*m_epsilon*m_sigma6;
    m_systemSize        = systemSize;
    m_systemSizeHalf    = {systemSize[0]/2.0, systemSize[1]/2.0, systemSize[2]/2.0};
    m_rCut              = rCut;
    m_rCut2             = rCut * rCut;
    m_neighbourCut      = neighbourCut;
    m_neighbourCut2     = neighbourCut*neighbourCut;
    m_neighbourList     = new NeighbourList(m_system, m_neighbourCut, m_rCut, m_systemSize);
    m_cellList          = m_neighbourList->getCellList();
    double r2           = 1.0 / m_rCut2;
    m_potentialAtCut    = 4*m_epsilon * r2*r2*r2 * m_sigma6 * (m_sigma6*r2*r2*r2-1);
}

void LennardJones::computeForces(const std::vector<Atom*> & atoms, int n) {

    if (m_timeStepsSinceLastCellListUpdate == -1 ||
        m_timeStepsSinceLastCellListUpdate >= 20) {
        m_timeStepsSinceLastCellListUpdate = 1;
        //m_cellList->updateCellLists();
        m_neighbourList->constructNeighbourLists();
    }
    m_timeStepsSinceLastCellListUpdate += 1;
    setForcesToZero(atoms, n);
    m_potentialEnergy       = 0;
    m_pressure              = 0;
    double dr2              = 0;
    double df               = 0;
    double dr[3]            = {0,0,0};


    for (int i=0; i<m_system->getN(); i++) {
        Atom* atom1 = at(m_system->getAtoms(), i);
        vector<Atom*> neighbours = m_neighbourList->getNeighbours(atom1->getIndex());

        for (int j=0; j<neighbours.size(); j++) {
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
                const double r2         = 1.0 / dr2;
                const double r6         = r2*r2*r2;
                const double sigma6r6   = m_sigma6 * r6;
                const int cut           = (dr2 < m_rCut2);
                const double f          = -m_24epsilon * sigma6r6 *
                                          (2*sigma6r6 - 1) * r2 * cut;
                m_potentialEnergy      += (m_4epsilonSigma6 * r6 *
                                           (sigma6r6 - 1) - m_potentialAtCut) * cut;

                for (int k=0; k < 3; k++) {
                    df = f * dr[k];
                    atom1->addForce(-df, k);
                    atom2->addForce( df, k);
                    //m_pressure += f * std::sqrt(dr2) * r2;
                }
            }
        }
    }
}



double LennardJones::computePotential(const std::vector<Atom*> & atoms, int n) {
    return m_potentialEnergy;
}

