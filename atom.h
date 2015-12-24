#pragma once
#include "vec.h"

class Atom {
public:
    Atom();

    void setPosition(vec position1);
    void setVelocity(vec velocity);
    void setForce   (vec force);
    void addForce   (vec dforce);
    void setMass    (double mass);

    double getMass()  {return this->mass;}
    vec getPosition() {return this->position;}
    vec getVelocity() {return this->velocity;}
    vec getForce()    {return this->force;}

private:
    double mass;
    vec position;
    vec velocity;
    vec force;
};
