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

    m_cells = vector<vector<vector<vector<Atom*>>>>(m_numberOfCellsInEachDirection);
    m_cells.reserve(m_numberOfCellsInEachDirection);
    for (int i=0; i<m_numberOfCellsInEachDirection; i++) {
        at(m_cells,i).reserve(m_numberOfCellsInEachDirection);
        for (int j=0; j<m_numberOfCellsInEachDirection; j++) {
            cout << "hei2" << endl;
            at(at(m_cells,i),j).reserve(m_numberOfCellsInEachDirection);
            for (int k=0; k<m_numberOfCellsInEachDirection; k++) {

                at(at(at(m_cells, i), j), k).reserve(m_numberOfCellsInEachDirection);
            }
        }
    }
}

void CellList::clearCells() {
    for (int i=0; i<m_numberOfCellsInEachDirection; i++) {
        for (int j=0; j<m_numberOfCellsInEachDirection; j++) {
            for (int k=0; k<m_numberOfCellsInEachDirection; k++) {
                at(at(at(m_cells,i),j),k).clear();
            }
        }
    }
}

void CellList::updateCellLists() {
    if (m_firstUpdate) {
        m_firstUpdate = false;
        setup();
    }

    for (int i=0; i<m_totalCells; i++) {
        clearCells();
    }
    for (int l=0; l<m_system->getN(); l++) {
        Atom* atom = at(m_system->getAtoms(),l);
        std::vector<double>& position   = at(m_system->getAtoms(),l)->getPosition();
        std::vector<double>& systemSize = m_system->getSystemSize();
        const int i = position[0] / systemSize[0] * m_numberOfCellsInEachDirection;
        const int j = position[1] / systemSize[1] * m_numberOfCellsInEachDirection;
        const int k = position[2] / systemSize[2] * m_numberOfCellsInEachDirection;
        at(m_system->getAtoms(),l)->setCellListIndex(i,j,k);

        if (i >= m_numberOfCellsInEachDirection ||
            j >= m_numberOfCellsInEachDirection ||
            k >= m_numberOfCellsInEachDirection) {
            cout << "atom #=" << l << endl;
            cout << "i=" << i << ", j=" << j << ", k=" << k << endl;
            cout << "pos=" << position[0] << ", " << position[1] << ", " << position[2] << endl;
        }
        at(at(at(m_cells,i),j),k).push_back(atom);
    }
}

int CellList::getSizeOfCellList(int i, int j, int k) {
    if (at(at(at(m_cells,i),j),k).empty()) {
        return 0;
    } else {
        return at(at(at(m_cells,i),j),k).size();
    }
}







