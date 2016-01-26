#pragma once
#include <vector>

class CellList {
public:
    CellList(class System* system, double rCut);
    void initializeCellLists();
    void computeCellLists(std::vector<class Atom*> atoms, int n);
    int computeCellNumber(double x, int index);
    int getNumberOfCellsInEachDirection() { return m_numberOfCellsInEachDirection; }
    bool isNeighbour(std::vector<int> atom1cellList,
                     std::vector<int> atom2cellList);

private:
    int m_numberOfCellsInEachDirection = 0;
    double m_rCut = 0;
    class System* m_system = nullptr;
    std::vector<double> m_systemSize;
};

