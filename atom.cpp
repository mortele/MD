#include "atom.h"

Atom::Atom() {
    this->position = vec();
    this->velocity = vec();
    this->force    = vec();
    this->mass     = 1.0;
}

void Atom::setPosition(vec position) {
    this->position = position;
}

void Atom::setVelocity(vec velocity) {
    this->velocity = velocity;
}

void Atom::setForce(vec force) {
    this->force = force;
}

void Atom::addForce(vec dforce) {
    this->force = this->force + dforce;

}

void Atom::setMass(double mass) {
    this->mass = mass;
}




