#pragma once
#include <vector>

class CellList {
public:
    CellList(class System* system, double rCut);
    void initializeCellLists();
    void computeCellLists(std::vector<class Atom*> atoms, int n);
    int computeCellNumber(int x, int y, int z);
    int computeCellNumber(std::vector<double> position);
    int getNumberOfCellsInEachDirection() { return m_numberOfCellsInEachDirection; }

private:
    int m_numberOfCellsInEachDirection = 0;
    double m_rCut = 0;
    class System* m_system = nullptr;
    std::vector<double> m_systemSize;
    std::vector<std::vector<class Atom*>> m_cells;
};

