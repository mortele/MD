#include "celllist.h"
#include <iostream>
#include "system.h"
#include "atom.h"

using std::cout;
using std::endl;


CellList::CellList(System* system, double rCut) {
    m_system = system;
    m_rCut = rCut;
}

void CellList::setup() {
    m_numberOfCellsInEachDirection = m_system->getSystemSize().at(0) / m_rCut;
    if (m_numberOfCellsInEachDirection < 1) {
        m_numberOfCellsInEachDirection = 1;
    }
    m_totalCells = m_numberOfCellsInEachDirection*
                   m_numberOfCellsInEachDirection*
                   m_numberOfCellsInEachDirection;
    m_cells.resize(m_totalCells);
}

void CellList::updateCellLists() {
    if (m_firstSetup) {
        m_firstSetup = false;
        setup();
    }

    for (int i=0; i<m_totalCells; i++) {
        m_cells.at(i).clear();
    }
    for (int l=0; l<m_system->getN(); l++) {
        Atom* atom = at(m_system->getAtoms(),l);
        std::vector<double>& position   = at(m_system->getAtoms(),l)->getPosition();
        std::vector<double>& systemSize = m_system->getSystemSize();
        const int i = position[0] / systemSize[0] * m_numberOfCellsInEachDirection;
        const int j = position[1] / systemSize[1] * m_numberOfCellsInEachDirection;
        const int k = position[2] / systemSize[2] * m_numberOfCellsInEachDirection;
        const int index = projectFromCellCoordinatesToIndex(i,j,k);
        at(m_system->getAtoms(),l)->setCellListIndex(index);
        if (index >= m_totalCells ||
            i >= m_numberOfCellsInEachDirection ||
            j >= m_numberOfCellsInEachDirection ||
            k >= m_numberOfCellsInEachDirection) {
            cout << "i=" << i << ", j=" << j << ", k=" << k << endl;
            cout << "index=" << index << ", m_total=" << m_totalCells << endl;
            cout << "pos=" << position[0] << ", " << position[1] << ", " << position[2] << endl;
        }
        at(m_cells,index).push_back(atom);
    }
}

void CellList::projectFromIndexToCellCoordinates(int index, int* coordinates) {
    coordinates[0] = index / (m_numberOfCellsInEachDirection*
                              m_numberOfCellsInEachDirection);
    coordinates[1] = (index / m_numberOfCellsInEachDirection) %
                     m_numberOfCellsInEachDirection;
    coordinates[2] = index % m_numberOfCellsInEachDirection;
}

int CellList::projectFromCellCoordinatesToIndex(const int* coordinates) {
    return projectFromCellCoordinatesToIndex(coordinates[0],
                                             coordinates[1],
                                             coordinates[2]);
}

int CellList::projectFromCellCoordinatesToIndex(int i, int j, int k) {
    return m_numberOfCellsInEachDirection *
            (m_numberOfCellsInEachDirection * i + j) + k;
}

int CellList::projectFromCellCoordinatesToIndexPeriodic(int i, int j, int k) {
    const int NC = m_numberOfCellsInEachDirection;
    return projectFromCellCoordinatesToIndex((i+NC) % NC, (j+NC) % NC, (k+NC) % NC);
    //return ( (i+NC) % NC)*NC*NC + ( (j+NC) % NC)*NC + ( (k+NC) % NC);
}







