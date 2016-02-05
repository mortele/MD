#pragma once
#include <vector>
#include "vec.h"

using std::vector;

class CellList {
public:
    CellList(class System* system, real rCut);
    void setup();
    void clearCells();
    void updateCellLists();
    int  getTotalNumberOfCells() { return m_totalCells; }
    int  getNumberOfCellsInEachDirection() { return m_numberOfCellsInEachDirection; }
    vector<class Atom*>& getCell(int i, int j, int k) { return at(at(at(m_cells, i), j), k); }

    int getSizeOfCellList(int i, int j, int k) {
        if (at(at(at(m_cells,i),j),k).empty()) {
            return 0;
        } else {
            return at(at(at(m_cells,i),j),k).size();
        }
    }



private:
    int             m_numberOfCellsInEachDirection = 0;
    int             m_totalCells = 0;
    bool            m_firstUpdate = true;
    real          m_rCut = 0;
    class System*   m_system = nullptr;
    vector<vector<vector<vector<class Atom*>>>> m_cells;
};
