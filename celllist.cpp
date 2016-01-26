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
                                              atoms.at(i)->getPosition().at(k), k), k);

        }
    }
}

int CellList::computeCellNumber(double x, int index) {
    return x / m_systemSize.at(index) * m_numberOfCellsInEachDirection;
}

bool CellList::isNeighbour(std::vector<int> atom1cellList,
                           std::vector<int> atom2cellList) {
    int* dist = new int[3];
    for (int k=0; k<3; k++) {
        dist[k] = atom2cellList.at(k) - atom1cellList.at(k);

        // Check if the two cell lists are neighbours over the periodic
        // boundary.
        if ((atom1cellList.at(k) == m_numberOfCellsInEachDirection) &&
            (atom2cellList.at(k) == 0)) {
            dist[k] == 1;
        }
    }

    // Both atoms in same cell list.
    if (dist[0] == 0 && dist[1] == 0 && dist[2] == 0) {
        return true;
    // Atom2 in the cell list directly next to the one containing atom1.
    } else if ((dist[0] == 1 && dist[1] == 0 && dist[2] == 0) ||
               (dist[0] == 0 && dist[1] == 1 && dist[2] == 0) ||
               (dist[0] == 0 && dist[1] == 0 && dist[2] == 1)) {
        return true;
    // Atom2 in the cell list diagonally next to the one containing atom1.
    } else if ((dist[0] == 1 && dist[1] == 1 && dist[2] == 0) ||
               (dist[0] == 0 && dist[1] == 1 && dist[2] == 1) ||
               (dist[0] == 1 && dist[1] == 0 && dist[2] == 1)) {
        return true;
    // Atom2 in the corner cell list from the one containing atom1.
    } else if (dist[0] == 1 && dist[1] == 1 && dist[2] == 1) {
        return true;
    } else {
        return false;
    }
}

