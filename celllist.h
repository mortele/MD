#pragma once
#include <vector>
#include "vec.h"

using std::vector;

class CellList {
public:
    CellList(class System* system, double rCut);
    void setup();
    void clearCells();
    void updateCellLists();
    int  getTotalNumberOfCells() { return m_totalCells; }
    int  getNumberOfCellsInEachDirection() { return m_numberOfCellsInEachDirection; }
    int  getSizeOfCellList(int i, int j, int k);
    vector<class Atom*>& getCell(int i, int j, int k);

private:
    int             m_numberOfCellsInEachDirection = 0;
    int             m_totalCells = 0;
    bool            m_firstUpdate = true;
    double          m_rCut = 0;
    class System*   m_system = nullptr;
    vector<vector<vector<vector<class Atom*>>>> m_cells;
};
