#pragma once
#include "../atom.h"
#include <vector>


class Potential {
public:
    Potential(class System* system);

    virtual void    computeForces   (const std::vector<Atom*> & atoms, int n) = 0;
    virtual double  computePotential(const std::vector<Atom*> & atoms, int n) = 0;
    virtual std::string getName() = 0;
    void setForcesToZero (const std::vector<Atom*> & atoms, int n);
    bool getCellListsActive()       { return m_cellListsActive; }
    double getRCUt()                { return m_rCut; }
    class CellList* getCellList()   { return m_cellList; }

protected:
    int     m_timeStepsSinceLastCellListUpdate = -1;
    bool    m_cellListsActive = false;
    double  m_rCut  = 0;
    double  m_rCut2 = 0;
    class CellList* m_cellList = nullptr;
    class System*   m_system = nullptr;
};

