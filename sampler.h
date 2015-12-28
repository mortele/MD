#pragma once
#include "Potentials/potential.h"
#include <iostream>
#include "vec.h"
#include "atom.h"
#include "system.h"


class Sampler {
public:
    Sampler();
    void setupSampler(Atom*, int);
    void setPotential(Potential*);
    void setNtDt(int, double);
    void sample(int);
    double sampleKineticEnergy();
    double samplePotentialEnergy();

    double*** getPositions() { return this->positions; }
    double*   getEnergies()  { return this->energies; }
    double*   getTime()      { return this->time; }

private:
    int        n;
    int        Nt;
    double     dt;
    double***  positions;
    double*    energies;
    double*    potentialEnergies;
    double*    kineticEnergies;
    double*    time;
    Atom*      atoms;
    Potential* potential;
};

