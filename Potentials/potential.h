#pragma once
#include "../atom.h"
#include <vector>


class Potential {
public:
    Potential();

    virtual void    computeForces   (std::vector<Atom*> atoms, int n) = 0;
    virtual double  computePotential(std::vector<Atom*> atoms, int n) = 0;
            void    setForcesToZero (std::vector<Atom*> atoms, int n);
    virtual std::string getName() = 0;
};

