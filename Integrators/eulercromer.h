#pragma once
#include "integrator.h"
#include "vec.h"
#include "../atom.h"

class EulerCromer : public Integrator {
public:
    EulerCromer(double dt);

    void advance(Atom *atoms, int n);
};

