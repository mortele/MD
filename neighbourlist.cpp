#include "neighbourlist.h"
#include "atom.h"
#include "celllist.h"
#include "system.h"
#include "elapsedtimer.h"

using std::vector;
using std::cout;
using std::endl;


NeighbourList::NeighbourList(System* system,
                             real rCut,
                             real neighbourCut,
                             vector<real> systemSize) {
    m_system        = system;
    m_rCut          = rCut;
    m_rCut2         = rCut*rCut;
    m_neighbourCut  = neighbourCut;
    m_neighbourCut2 = neighbourCut*neighbourCut;
    m_cellList      = new CellList(system, rCut);
    m_firstUpdate   = true;
    m_systemSize    = systemSize;
}

void NeighbourList::constructNeighbourLists() {
    if (m_firstUpdate) {
        m_systemSizeHalf.resize(3);
        for (int k=0; k<3; k++) {
            at(m_systemSizeHalf,k) = 0.5 * at(m_systemSize,k);
        }
        m_neighbours.resize(m_system->getN(), vector<Atom*>());
        m_neighbourIndices.resize(m_system->getN(), vector<int>());
        for(int i=0; i<m_system->getN(); i++) {
            m_neighbours[i].reserve(500);
            m_neighbourIndices[i].reserve(500);
        }
        m_firstUpdate = false;
    }
    ElapsedTimer::getInstance().m_updateCellList.start();
    clearNeighbours();
    m_cellList->updateCellLists();
    ElapsedTimer::getInstance().m_updateCellList.stop();

    real dr2              = 0;
    real dr[3]            = {0,0,0};
    ElapsedTimer::getInstance().m_updateNeighborList.start();
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
                Atom* atom1 = at(m_cellList->getCell(ci,  cj,  ck),  i);

            for (int j=(di==0 && dj==0 && dk==0)*(i+1); j<m_cellList->getSizeOfCellList(cii, cjj, ckk); j++) {
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

                if (dr2 < m_neighbourCut2) {
                    at(m_neighbours,atom1->getIndex()).push_back(atom2);
                    at(m_neighbourIndices, atom1->getIndex()).push_back(atom2->getIndex());
                }
            }}
        }}}
    }}}

    for(Atom *atom : m_system->getAtoms()) {
        atom->didUpdateNeighborlist();
    }

    ElapsedTimer::getInstance().m_updateNeighborList.stop();
}

void NeighbourList::clearNeighbours() {
    for (int i=0; i<m_system->getN(); i++) {
        at(m_neighbours,i).clear();
        at(m_neighbourIndices,i).clear();
    }
}

