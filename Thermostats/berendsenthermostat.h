#pragma once
#include "thermostat.h"
#include <vector>
#include "../vec.h"

class Atom;

class BerendsenThermostat : public Thermostat {
public:
    BerendsenThermostat(class System* system, real targetTemperature, real tau, real dt);
    void adjustVelocities(real instantaneousTemperature);

private:
    real m_tau;
    real m_dtOverTau;
};

