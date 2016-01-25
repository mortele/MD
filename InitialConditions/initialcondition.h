#pragma once
#include "../atom.h"
#include <vector>

class InitialCondition {
public:
    InitialCondition();

    virtual std::string getName() = 0;
    virtual void  setupInitialCondition() = 0;

    void    removeLinearMomentum();
    std::vector<Atom*>   getAtoms()  { return this->atoms; }
    int     getN()      { return this->n; }
    std::vector<double> getTotalMomentum() { return this->totalMomentum; }


protected:
    int   n = 0;
    std::vector<Atom*> atoms = std::vector<Atom*>();
    bool  setupDone = false;
    std::vector<double> totalMomentum = std::vector<double>(3);
};

