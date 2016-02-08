#pragma once
#include "potential.h"
#include <tgmath.h>


class Gravitational : public Potential {
public:
    Gravitational(real G, class System* system);
    Gravitational(real G, real eps, class System* system);
    void   computeForces    ();
    real computePotential ();
    std::string getName() { return "Gravitational"; }

private:
    real m_G = 0;
    real m_eps = 0;
    real m_potentialEnergy = 0;
};

