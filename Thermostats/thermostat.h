#pragma once
#include <vector>
#include "vec.h"

class Atom;

class Thermostat {
public:
    Thermostat(class System* system, real targetTemperature, real dt);
    virtual void adjustVelocities(real instantaneousTemperature) = 0;
    real getTargetTemperature() { return m_targetTemperature; }
    void setTargetTemperature(real targetTemperature) { m_targetTemperature = targetTemperature; }

protected:
    real m_targetTemperature = 0;
    real m_dt = 0;
    class System* m_system = nullptr;
};


