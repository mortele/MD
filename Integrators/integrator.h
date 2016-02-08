#pragma once
#include "../atom.h"
#include <string>
#include <vector>

class Integrator {
public:
    Integrator(real dt, class System* system);
    virtual void advance() = 0;
    void   setPotential(class Potential* potential);
    real getTimeStep() { return m_dt; }
    virtual std::string getName() = 0;

protected:
    real              m_dt = 0;
    class System*     m_system = nullptr;
    class Potential*  m_potential = nullptr;
};
