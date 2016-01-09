#include "atom.h"

Atom::Atom() {
    this->position = vec();
    this->velocity = vec();
    this->force    = vec();
    this->mass     = 1.0;
}

Atom::Atom(std::string name, double mass) {
    this->position = vec();
    this->velocity = vec();
    this->force    = vec();
    this->mass     = mass;
    this->name     = name;
}

Atom::Atom(double mass) {
    this->position = vec();
    this->velocity = vec();
    this->force    = vec();
    this->mass     = mass;
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

void Atom::setName(std::string name) {
    this->name = name;
}




