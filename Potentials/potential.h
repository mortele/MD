#pragma once
#include "../atom.h"
#include <vector>


class Potential {
public:
    Potential(class System* system);

    virtual void    computeForces   (std::vector<Atom*> atoms, int n) = 0;
    virtual double  computePotential(std::vector<Atom*> atoms, int n) = 0;
    virtual std::string getName() = 0;
    void setForcesToZero (std::vector<Atom*> atoms, int n);
    bool getCellListsActive()       { return this->cellListsActive; }
    double getRCUt()                { return this->rCut; }
    class CellList* getCellList()   { return this->cellList; }

protected:
    int  timeStepsSinceLastCellListUpdate = -1;
    bool cellListsActive = false;
    double rCut = 0;
    class CellList* cellList = nullptr;
    class System*   system = nullptr;
};

