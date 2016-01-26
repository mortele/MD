#pragma once
#include "../atom.h"
#include <vector>

class InitialCondition {
public:
    InitialCondition();

    virtual std::string getName() = 0;
    virtual void  setupInitialCondition() = 0;

    void    removeLinearMomentum();
    std::vector<Atom*>   getAtoms()  { return m_atoms; }
    int     getN()      { return m_n; }
    std::vector<double> getTotalMomentum() { return m_totalMomentum; }


protected:
    int                 m_n             = 0;
    std::vector<Atom*>  m_atoms         = std::vector<Atom*>();
    bool                m_setupDone     = false;
    std::vector<double> m_totalMomentum = std::vector<double>(3);
};

