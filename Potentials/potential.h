#pragma once
#include "../atom.h"


class Potential {
public:
    Potential();

    virtual void    computeForces   (Atom* atoms, int n) = 0;
    virtual double  computePotential(Atom* atoms, int n) = 0;
            void    setForcesToZero (Atom* atom, int n);
    virtual std::string getName() = 0;
};

