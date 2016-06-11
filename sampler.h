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
    void setNtDt(int, real);
    void sample(int);
    real sampleKineticEnergy();
    real samplePotentialEnergy();
    real samplePressure(real);
    real sampleMeanSquareDisplacement();
    void setPressureSamplingEnabled(bool enabled);

    //real*** getPositions() { return this->positions; }
    real*   getEnergies()                 { return m_energies; }
    real*   getTime()                     { return m_time; }
    real*   getPressures()                { return m_pressures; }
    real*   getInstantanousTemperature()  { return m_instantanousTemperature; }
    real*   getKineticEnergies()          { return m_kineticEnergies; }
    real*   getPotentialEnergies()        { return m_potentialEnergies; }
    real*   getMeanSquareDisplacement()   { return m_meanSquareDisplacement; }

private:
    int                 m_n                         = 0;
    int                 m_Nt                        = 0;
    bool                m_pressureSamplingEnabled   = false;
    real                m_volume                    = 0;
    real                m_density                   = 0;
    real                m_dt                        = 0;
    real*               m_energies                  = nullptr;
    real*               m_potentialEnergies         = nullptr;
    real*               m_kineticEnergies           = nullptr;
    real*               m_time                      = nullptr;
    real*               m_instantanousTemperature   = nullptr;
    real*               m_pressures                 = nullptr;
    real*               m_meanSquareDisplacement    = nullptr;
    std::vector<Atom*>  m_atoms;
    Potential*          m_potential                 = nullptr;
    System*             m_system                    = nullptr;
};

