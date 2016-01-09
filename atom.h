#pragma once
#include "vec.h"

class Atom {
public:
    Atom();
    Atom(double mass);
    Atom(std::string name, double mass);

    void setPosition(vec position1);
    void setVelocity(vec velocity);
    void setForce   (vec force);
    void addForce   (vec dforce);
    void setMass    (double mass);
    void setName    (std::string name);

    double      getMass()     { return this->mass; }
    vec         getPosition() { return this->position; }
    vec         getVelocity() { return this->velocity; }
    vec         getForce()    { return this->force; }
    std::string getName()     { return this->name; }

private:
    double mass;
    vec position;
    vec velocity;
    vec force;
    std::string name = "Ar";
};
