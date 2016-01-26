#pragma once
#include <vector>

class Atom;

class Thermostat {
public:
    Thermostat();
    virtual void adjustVelocities(const std::vector<Atom*> & atoms, int n, double instantaneousTemperature) = 0;
};

