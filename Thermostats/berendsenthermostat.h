#pragma once
#include "thermostat.h"
#include <vector>

class Atom;

class BerendsenThermostat : public Thermostat {
public:
    BerendsenThermostat(double targetTemperature, double tau, double dt);
    void adjustVelocities(const std::vector<Atom*> & atom, int n, double instantaneousTemperature);

private:
    double m_tau;
    double m_dtOverTau;
};

