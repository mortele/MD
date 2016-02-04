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
    double getRCUt()                { return m_rCut; }
    class CellList* getCellList()   { return m_cellList; }
    double getPressure()            { return m_pressure; }

protected:
    int                     m_timeStepsSinceLastCellListUpdate  = -1;
    double                  m_rCut                              = 0;
    double                  m_rCut2                             = 0;
    double                  m_neighbourCut                      = 0;
    double                  m_neighbourCut2                     = 0;
    double                  m_pressure                          = 0;
    class CellList*         m_cellList                          = nullptr;
    class NeighbourList*    m_neighbourList                     = nullptr;
    class System*           m_system                            = nullptr;
};

