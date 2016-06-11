#pragma once
#include "thermostat.h"
#include <vector>
#include "../vec.h"
#include "../random.h"

class AndersenThermostat : public Thermostat {
public:
    AndersenThermostat(class System* system, real targetTemperature, real tau, real dt);
    void adjustVelocities(real instantaneousTemperature);

private:
    real m_tau;
    real m_dtOverTau;
};

