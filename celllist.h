#pragma once
#include <vector>

using std::vector;

class CellList {
public:
    CellList(class System* system, double rCut);
    void setup();
    void updateCellLists();

private:
    int             m_numberOfCellsInEachDirection = 0;
    double          m_rCut = 0;
    class System*   m_system = nullptr;
    vector<vector<class Atom*>> m_cells;
};







/*public:
    CellList(class System* system, double rCut);
    void initializeCellLists();
    void computeCellLists(const std::vector<class Atom*> & atoms, int n);
    int computeCellNumber(double x, int index);
    int getNumberOfCellsInEachDirection() { return m_numberOfCellsInEachDirection; }
    bool isNeighbour(const std::vector<int> & atom1cellList,
                     const std::vector<int> & atom2cellList);

private:
    int                 m_numberOfCellsInEachDirection = 0;
    bool                m_firstComputation = true;
    double              m_rCut = 0;
    class System*       m_system = nullptr;
    std::vector<double> m_systemSize;
    std::vector<int>    dist;*/
