#pragma once
#include "integrator.h"
#include "vec.h"
#include <vector>

class EulerCromer : public Integrator {
public:
    EulerCromer(real dt, class System* system);
    void advance();
    std::string getName() { return "Euler-Cromer"; }
};

