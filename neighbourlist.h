#pragma once
#include <vector>
#include "vec.h"

class NeighbourList {
public:
    NeighbourList(class System* system, double rCut, double neighbourCut, std::vector<double> systemSize);
    void constructNeighbourLists();
    void clearNeighbours();
    class CellList*          getCellList()           { return m_cellList; }
    std::vector<class Atom*> getNeighbours(int i)    { return at(m_neighbours,i); }

private:
    double          m_rCut              = 0;
    double          m_rCut2             = 0;
    double          m_neighbourCut      = 0;
    double          m_neighbourCut2     = 0;
    bool            m_firstUpdate       = true;
    class System*   m_system            = nullptr;
    class CellList* m_cellList          = nullptr;
    std::vector<std::vector<class Atom*>> m_neighbours;
    std::vector<double>                   m_systemSize;
    std::vector<double>                   m_systemSizeHalf;
};

