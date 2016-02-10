#include "lennardjonesneighbourlists.h"
#include "../celllist.h"
#include "../neighbourlist.h"
#include "../system.h"
#include "../elapsedtimer.h"
using std::cout;
using std::endl;

LennardJonesNeighbourLists::LennardJonesNeighbourLists(std::vector<real>  systemSize,
                           real               rCut,
                           System*              system) :
    LennardJonesNeighbourLists(1.0, 3.405, systemSize, rCut, rCut, system) {
}

LennardJonesNeighbourLists::LennardJonesNeighbourLists(real               epsilon,
                           real               sigma,
                           std::vector<real>  systemSize,
                           real               rCut,
                           real               neighbourCut,
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
    m_neighbourCut      = neighbourCut;
    m_neighbourCut2      = neighbourCut*neighbourCut;
    m_neighbourList     = new NeighbourList(m_system, m_rCut, m_neighbourCut, m_systemSize);
    m_cellList          = m_neighbourList->getCellList();
    real r2           = 1.0f / m_rCut2;
    m_potentialAtCut    = 4*m_epsilon * r2*r2*r2 * m_sigma6 * (m_sigma6*r2*r2*r2-1);

    delx = new real[1000];
    dely = new real[1000];
    delz = new real[1000];
    delr2 = new real[1000];
    jindex = new int[1000];
}

//void LennardJonesNeighbourLists::computeForces() {
//    if (m_timeStepsSinceLastCellListUpdate == -1 ||
//        m_timeStepsSinceLastCellListUpdate >= 20) {
//        m_timeStepsSinceLastCellListUpdate = 1;
//        m_neighbourList->constructNeighbourLists();
//    }
////    real shellThickness = m_neighbourList->getShellThickness();
////    for(Atom *atom : m_system->getAtoms()) {
////        if(atom->needToUpdateNeighborList(shellThickness)) {
////            m_neighbourList->constructNeighbourLists();
////            break;
////        }
////    }

//    m_timeStepsSinceLastCellListUpdate += 1;
//    ElapsedTimer::getInstance().m_calculateForces.start();
//    setForcesToZero();
//    m_potentialEnergy       = 0;
//    m_pressure              = 0;
//    real_posvel * __restrict const x = Atom::positions;
//    real_posvel * __restrict const f = Atom::forces;

//    for (int i=0; i<m_system->getN(); i++) {
//        const vector<int> &neighbours = m_neighbourList->getNeighbourIndices(i);
//        real fxi = 0;
//        real fyi = 0;
//        real fzi = 0;
//        real potentialEnergy = 0;
//        const int *__restrict c_neighbours = &neighbours.front();

//        int numNeighbors = 0;

//// #pragma simd reduction(+:fxi, fyi, fzi, potentialEnergy)
//        for (unsigned int jj=0; jj<neighbours.size(); jj++) {
//            const int j = c_neighbours[jj];

//            real dr[3] = {0.0f, 0.0f, 0.0f};

//            real dr2 = 0;
//            for (int k=0; k < 3; k++) {
//                dr[k] = x[3*i+k] - x[3*j+k];
//                if (dr[k] > m_systemSizeHalf[k]) {
//                    dr[k] = dr[k] - m_systemSize[k];
//                } else if (dr[k] < -m_systemSizeHalf[k]) {
//                    dr[k] = dr[k] + m_systemSize[k];
//                }
//                dr2 += dr[k]*dr[k];
//            }

//            if(dr2 < m_rCut2) {
//                delx[numNeighbors] = dr[0];
//                dely[numNeighbors] = dr[1];
//                delz[numNeighbors] = dr[2];
//                delr2[numNeighbors] = dr2;
//                jindex[numNeighbors] = j;
//                numNeighbors++;
//            }
//        }
//        int padWidth = 32/sizeof(real);
//        int numNeighborsPadded = numNeighbors;
//        while(numNeighborsPadded % padWidth != 0) {
//            delx[numNeighborsPadded] = 0;
//            dely[numNeighborsPadded] = 0;
//            delz[numNeighborsPadded] = 0;
//            delr2[numNeighborsPadded] = 10000;
//            jindex[numNeighborsPadded] = 100000;
//            numNeighborsPadded++;
//        }

//#pragma vector aligned
//#pragma simd reduction(+:fxi, fyi, fzi, potentialEnergy)
//        for(int jj=0; jj<numNeighborsPadded; jj++) {
//            const real r2         = 1.0f / delr2[jj];
//            const real r6         = r2*r2*r2;
//            const real sigma6r6   = m_sigma6 * r6;
//            const real fpair          = -m_24epsilon * sigma6r6 *
//                                      (2.0f*sigma6r6 - 1.0f) * r2 * (delr2[jj] < m_rCut2);
//            potentialEnergy      += (m_4epsilonSigma6 * r6 *
//                                       (sigma6r6 - 1.0f) - m_potentialAtCut)*(delr2[jj] < m_rCut2);
//            const int j = jindex[jj];
//            f[3*j+0] += fpair * delx[jj];
//            f[3*j+1] += fpair * dely[jj];
//            f[3*j+2] += fpair * delz[jj];
//            fxi -= fpair * delx[jj];
//            fyi -= fpair * dely[jj];
//            fzi -= fpair * delz[jj];
//        }

//        f[3*i+0] += fxi;
//        f[3*i+1] += fyi;
//        f[3*i+2] += fzi;
//        m_potentialEnergy += potentialEnergy;
//    }

//    ElapsedTimer::getInstance().m_calculateForces.stop();
//}


void LennardJonesNeighbourLists::computeForces() {

    if (m_timeStepsSinceLastCellListUpdate == -1 ||
        m_timeStepsSinceLastCellListUpdate >= 20) {
        m_timeStepsSinceLastCellListUpdate = 1;
        m_neighbourList->constructNeighbourLists();
    }
    m_timeStepsSinceLastCellListUpdate += 1;
    setForcesToZero();
    m_potentialEnergy       = 0;
    m_pressure              = 0;
    real_posvel * __restrict const x = Atom::positions;
    real_posvel * __restrict const f = Atom::forces;

    for (int i=0; i<m_system->getN(); i++) {
        const vector<int> &neighbours = m_neighbourList->getNeighbourIndices(i);
        real fxi = 0;
        real fyi = 0;
        real fzi = 0;
        real potentialEnergy = 0;
        const unsigned int numNeighbors = neighbours.size();
        const int *__restrict c_neighbours = &neighbours.front();

// #pragma simd reduction(+:fxi, fyi, fzi, potentialEnergy)
        for (unsigned int jj=0; jj<numNeighbors; jj++) {
            const int j = c_neighbours[jj];

            real dr[3] = {0.0f, 0.0f, 0.0f};

            real dr2 = 0;
            for (int k=0; k < 3; k++) {
                dr[k] = x[3*i+k] - x[3*j+k];
                if (dr[k] > m_systemSizeHalf[k]) {
                    dr[k] = dr[k] - m_systemSize[k];
                } else if (dr[k] < -m_systemSizeHalf[k]) {
                    dr[k] = dr[k] + m_systemSize[k];
                }
                dr2 += dr[k]*dr[k];
            }

            const real r2         = 1.0f / dr2;
            const real r6         = r2*r2*r2;
            const real sigma6r6   = m_sigma6 * r6;
            const real cut           = (real)(dr2 < m_rCut2);
            const real fpair          = -m_24epsilon * sigma6r6 *
                                      (2*sigma6r6 - 1) * r2 * cut;
            potentialEnergy      += (m_4epsilonSigma6 * r6 *
                                       (sigma6r6 - 1) - m_potentialAtCut) * cut;

            for (int k=0; k < 3; k++) {
                const real df = fpair * dr[k];
                f[3*j+k] += df;
            }

            fxi -= fpair*dr[0];
            fyi -= fpair*dr[1];
            fzi -= fpair*dr[2];
        }

        f[3*i+0] += fxi;
        f[3*i+1] += fyi;
        f[3*i+2] += fzi;
        m_potentialEnergy += potentialEnergy;
    }
}

//void LennardJonesNeighbourLists::computeForces() {

//    if (m_timeStepsSinceLastCellListUpdate == -1 ||
//        m_timeStepsSinceLastCellListUpdate >= 20) {
//        m_timeStepsSinceLastCellListUpdate = 1;
//        m_neighbourList->constructNeighbourLists();
//    }
//    m_timeStepsSinceLastCellListUpdate += 1;
//    setForcesToZero();
//    m_potentialEnergy       = 0;
//    m_pressure              = 0;
//    // real dr2              = 0;
//    // real dr[3]            = {0,0,0};

//    for (int i=0; i<m_system->getN(); i++) {
//        Atom* atom1 = at(m_system->getAtoms(), i);
//        vector<Atom*> neighbours = m_neighbourList->getNeighbours(atom1->getIndex());
//        real fxi = 0;
//        real fyi = 0;
//        real fzi = 0;
//        real potentialEnergy = 0;
//        const unsigned int numNeighbors = neighbours.size();

//        real posi[3];
//        posi[0] = at(atom1->getPosition(),0); posi[1] = at(atom1->getPosition(),1); posi[2] = at(atom1->getPosition(),2);
//        real systemSize[3];
//        systemSize[0] = m_systemSize[0];
//        systemSize[1] = m_systemSize[1];
//        systemSize[2] = m_systemSize[2];
//        Atom ** __restrict const c_neighbours = &neighbours.front();

//// #pragma simd reduction(+:fxi, fyi, fzi, potentialEnergy)
//        for (unsigned int j=0; j<numNeighbors; j++) {
//            // Atom* atom2 = at(neighbours, j);
//            Atom *atom2 = c_neighbours[j];

//            real dr2 = 0;
//            real dr[3] = {0,0,0};

//            for (int k=0; k < 3; k++) {
//                dr[k] = posi[k] - at(atom2->getPosition(),k);
//                if (dr[k] > 0.5*systemSize[k]) {
//                    dr[k] = dr[k] - systemSize[k];
//                } else if (dr[k] < -0.5*systemSize[k]) {
//                    dr[k] = dr[k] + systemSize[k];
//                }
//                dr2 += dr[k]*dr[k];
//            }

//            const real r2         = 1.0f / dr2;
//            const real r6         = r2*r2*r2;
//            const real sigma6r6   = m_sigma6 * r6;
//            const real cut           = (real)(dr2 < m_rCut2);
//            const real f          = -m_24epsilon * sigma6r6 *
//                                      (2*sigma6r6 - 1) * r2 * cut;
//            potentialEnergy      += (m_4epsilonSigma6 * r6 *
//                                       (sigma6r6 - 1) - m_potentialAtCut) * cut;

//            for (int k=0; k < 3; k++) {
//                const real df = f * dr[k];
//                // atom1->addForce(-df, k);
//                atom2->addForce( df, k);
//                //m_pressure += f * std::sqrt(dr2) * r2;
//            }
//            fxi -= f*dr[0];
//            fyi -= f*dr[1];
//            fzi -= f*dr[2];
//        }

//        atom1->addForce(fxi, 0);
//        atom1->addForce(fyi, 1);
//        atom1->addForce(fzi, 2);
//        m_potentialEnergy += potentialEnergy;
//    }
//}

real LennardJonesNeighbourLists::computePotential() {
    return m_potentialEnergy;
}

