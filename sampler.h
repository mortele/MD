#pragma once
#include "Potentials/potential.h"
#include <iostream>
#include <vector>
#include "vec.h"
#include "atom.h"
#include "system.h"


class Sampler {
public:
    Sampler();
    void setupSampler(std::vector<Atom*> atoms, int);
    void setPotential(Potential*);
    void setNtDt(int, double);
    void sample(int);
    double sampleKineticEnergy();
    double samplePotentialEnergy();

    //double*** getPositions() { return this->positions; }
    double*   getEnergies()  { return this->energies; }
    double*   getTime()      { return this->time; }
    double*   getInstantanousTemperature() { return this->instantanousTemperature; }

private:
    int        n = 0;
    int        Nt = 0;
    double     dt = 0;
    double*    energies = nullptr;
    double*    potentialEnergies = nullptr;
    double*    kineticEnergies = nullptr;
    double*    time = nullptr;
    double*    instantanousTemperature = nullptr;
    std::vector<Atom*> atoms;
    Potential* potential = nullptr;
};

