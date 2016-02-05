#pragma once
#include "thermostat.h"
#include <vector>
#include "../vec.h"

class Atom;

class BerendsenThermostat : public Thermostat {
public:
    BerendsenThermostat(real targetTemperature, real tau, real dt);
    void adjustVelocities(const std::vector<Atom*> & atom, int n, real instantaneousTemperature);

private:
    real m_tau;
    real m_dtOverTau;
};

