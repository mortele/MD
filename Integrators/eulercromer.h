#pragma once
#include "integrator.h"
#include "vec.h"
#include <vector>
#include "../atom.h"

class EulerCromer : public Integrator {
public:
    EulerCromer(double dt);
    void advance(std::vector<Atom*> atoms, int n);
    std::string getName() { return "Euler-Cromer"; }
};

