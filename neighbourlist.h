#pragma once
#include <vector>
#include "vec.h"

class NeighbourList {
public:
    NeighbourList(class System* system, real rCut, real neighbourCut, std::vector<real> systemSize);
    void constructNeighbourLists();
    void clearNeighbours();
    class CellList*           getCellList()           { return m_cellList; }
    std::vector<class Atom*>& getNeighbours(int i)    { return at(m_neighbours,i); }

private:
    real          m_rCut              = 0;
    real          m_rCut2             = 0;
    real          m_neighbourCut      = 0;
    real          m_neighbourCut2     = 0;
    bool            m_firstUpdate       = true;
    class System*   m_system            = nullptr;
    class CellList* m_cellList          = nullptr;
    std::vector<std::vector<class Atom*>> m_neighbours;
    std::vector<real>                   m_systemSize;
    std::vector<real>                   m_systemSizeHalf;
};

