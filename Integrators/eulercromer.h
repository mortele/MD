#pragma once
#include "integrator.h"
#include "vec.h"
#include <vector>
#include "../atom.h"

class EulerCromer : public Integrator {
public:
    EulerCromer(real dt);
    void advance(const std::vector<Atom*> & atoms, int n);
    std::string getName() { return "Euler-Cromer"; }
};

