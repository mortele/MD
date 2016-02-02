#pragma once
#include "Potentials/potential.h"
#include <iostream>
#include <vector>
#include "vec.h"
#include "atom.h"
#include "system.h"


class Sampler {
public:
    Sampler(System* system);
    void setupSampler(std::vector<Atom*> atoms, int);
    void setPotential(Potential*);
    void setNtDt(int, double);
    void sample(int);
    double sampleKineticEnergy();
    double samplePotentialEnergy();
    double samplePressure(double);
    void   setPressureSamplingEnabled(bool enabled);

    //double*** getPositions() { return this->positions; }
    double*   getEnergies()                 { return m_energies; }
    double*   getTime()                     { return m_time; }
    double*   getPressures()                { return m_pressures; }
    double*   getInstantanousTemperature()  { return m_instantanousTemperature; }
    double*   getKineticEnergies()          { return m_kineticEnergies; }
    double*   getPotentialEnergies()        { return m_potentialEnergies; }

private:
    int                 m_n = 0;
    int                 m_Nt = 0;
    bool                m_pressureSamplingEnabled = false;
    double              m_volume = 0;
    double              m_density = 0;
    double              m_dt = 0;
    double*             m_energies = nullptr;
    double*             m_potentialEnergies = nullptr;
    double*             m_kineticEnergies = nullptr;
    double*             m_time = nullptr;
    double*             m_instantanousTemperature = nullptr;
    double*             m_pressures = nullptr;
    std::vector<Atom*>  m_atoms;
    Potential*          m_potential = nullptr;
    System*             m_system = nullptr;
};

