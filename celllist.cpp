#include "celllist.h"
#include "system.h"

CellList::CellList(System* system, double rCut) {
    m_rCut = rCut;
    m_system = system;
    m_systemSize = system->getSystemSize();
}

void CellList::initializeCellLists() {
    m_numberOfCellsInEachDirection = m_systemSize.at(0) / m_rCut;
    m_cells.resize(m_numberOfCellsInEachDirection*
                   m_numberOfCellsInEachDirection*
                   m_numberOfCellsInEachDirection);
}

int CellList::computeCellNumber(int x, int y, int z) {
    return  x*m_numberOfCellsInEachDirection*m_numberOfCellsInEachDirection +
            y*m_numberOfCellsInEachDirection +
            z;
}

int CellList::computeCellNumber(std::vector<double> position) {
    return computeCellNumber(position.at(0) / m_systemSize.at(0) * m_numberOfCellsInEachDirection,
                             position.at(1) / m_systemSize.at(1) * m_numberOfCellsInEachDirection,
                             position.at(2) / m_systemSize.at(2) * m_numberOfCellsInEachDirection);

    return ( (cx+m_numberOfCellsX) % m_numberOfCellsX)*m_numberOfCellsY*m_numberOfCellsZ +
            ( (cy+m_numberOfCellsY) % m_numberOfCellsY)*m_numberOfCellsZ +
            ( (cz+m_numberOfCellsZ) % m_numberOfCellsZ);
}

