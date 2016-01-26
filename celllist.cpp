#include "celllist.h"
#include <iostream>
#include "system.h"
#include "atom.h"

using std::cout;
using std::endl;

CellList::CellList(System* system, double rCut) {
    m_rCut = rCut;
    m_system = system;
    m_systemSize = system->getSystemSize();
}

void CellList::initializeCellLists() {
    m_numberOfCellsInEachDirection = m_systemSize.at(0) / m_rCut;
}

void CellList::computeCellLists(std::vector<Atom*> atoms, int n) {
    for (int i=0; i<m_system->getN(); i++) {
        for (int k=0; k<3; k++) {
            atoms.at(i)->setCellListIndex(this->computeCellNumber(
                                              atoms.at(i)->getPosition.at(k), k), k);
        }
    }
}

int CellList::computeCellNumber(double x, int index) {
    return x / m_systemSize.at(index) * m_numberOfCellsInEachDirection;
}

