#pragma once
#include "../atom.h"
#include <vector>


class Potential {
public:
    Potential(class System* system);

    virtual void    computeForces   (const std::vector<Atom*> & atoms, int n) = 0;
    virtual real  computePotential(const std::vector<Atom*> & atoms, int n) = 0;
    virtual std::string getName() = 0;
    void setForcesToZero (const std::vector<Atom*> & atoms, int n);
    real getRCUt()                { return m_rCut; }
    class CellList* getCellList() { return m_cellList; }
    real getPressure()            { return m_pressure; }

protected:
    int                     m_timeStepsSinceLastCellListUpdate  = -1;
    real                    m_rCut                              = 0;
    real                    m_rCut2                             = 0;
    real                    m_neighbourCut                      = 0;
    real                    m_neighbourCut2                     = 0;
    real                    m_pressure                          = 0;
    class CellList*         m_cellList                          = nullptr;
    class NeighbourList*    m_neighbourList                     = nullptr;
    class System*           m_system                            = nullptr;
};

