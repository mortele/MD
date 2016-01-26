#pragma once
#include <vector>

class Atom;

class Thermostat {
public:
    Thermostat(double targetTemperature, double dt);
    virtual void adjustVelocities(const std::vector<Atom*> & atoms, int n, double instantaneousTemperature) = 0;
    double getTargetTemperature() { return m_targetTemperature; }
    void setTargetTemperature(double targetTemperature) { m_targetTemperature = targetTemperature; }

protected:
    double m_targetTemperature = 0;
    double m_dt = 0;
};

