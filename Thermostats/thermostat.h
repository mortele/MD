#pragma once

class Atom;

class Thermostat {
public:
    Thermostat();
    virtual void adjustVelocities(Atom* atoms, int n, double instantaneousTemperature) = 0;
};

