#pragma once
#include <vector>
#include "vec.h"

class Atom;

class Thermostat {
public:
    Thermostat(real targetTemperature, real dt);
    virtual void adjustVelocities(const std::vector<Atom*> & atoms, int n, real instantaneousTemperature) = 0;
    real getTargetTemperature() { return m_targetTemperature; }
    void setTargetTemperature(real targetTemperature) { m_targetTemperature = targetTemperature; }

protected:
    real m_targetTemperature = 0;
    real m_dt = 0;
};

