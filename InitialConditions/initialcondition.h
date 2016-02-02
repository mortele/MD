#pragma once
#include <vector>

class InitialCondition {
public:
    InitialCondition();

    virtual std::string getName() = 0;
    virtual void  setupInitialCondition() = 0;

    void    removeLinearMomentum();
    int     getN()                         { return m_n; }
    std::vector<double> getTotalMomentum() { return m_totalMomentum; }
    std::vector<class Atom*>    getAtoms() { return m_atoms; }

protected:
    int                 m_n             = 0;
    bool                m_setupDone     = false;
    std::vector<double> m_totalMomentum = std::vector<double>(3);
    std::vector<class Atom*>  m_atoms   = std::vector<class Atom*>();
};

