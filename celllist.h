#pragma once
#include <vector>

using std::vector;

class CellList {
public:
    CellList(class System* system, double rCut);
    void setup();
    void updateCellLists();
    void projectFromIndexToCellCoordinates(int index, int* coordinates);
    int  projectFromCellCoordinatesToIndex(const int* coordinates);
    int  projectFromCellCoordinatesToIndex(int i, int j, int k);
    int  projectFromCellCoordinatesToIndexPeriodic(int i, int j, int k);
    void computeNeighbourIndices(int iCell, int* indices);
    int  getTotalNumberOfCells() { return m_totalCells; }
    int  getNumberOfCellsInEachDirection() { return m_numberOfCellsInEachDirection; }
    int  getSizeOfCellList(int index) { if (m_cells.at(index).empty()) {return 0;} else {return m_cells.at(index).size(); }}
    vector<class Atom*>& getCell(int i)     { return m_cells.at(i); }
    vector<class Atom*>& operator[](int i)  { return m_cells.at(i); }


private:
    int             m_numberOfCellsInEachDirection = 0;
    int             m_totalCells = 0;
    bool            m_firstSetup = true;
    double          m_rCut = 0;
    class System*   m_system = nullptr;
    vector<vector<class Atom*>> m_cells;

};
