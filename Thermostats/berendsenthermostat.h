#pragma once
#include "thermostat.h"

class Atom;

class BerendsenThermostat : public Thermostat {
public:
    BerendsenThermostat(double targetTemperature, double tau, double dt);
    void adjustVelocities(Atom* atom, int n, double instantaneousTemperature);

private:
    double targetTemperature;
    double tau;
    double dt;
    double dtOverTau;
};

