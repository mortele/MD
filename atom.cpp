#include "atom.h"

Atom::Atom() {
}

Atom::Atom(std::string name, double mass) {
    this->mass     = mass;
    this->name     = name;
}

Atom::Atom(double mass) {
    this->mass     = mass;
}

void Atom::setPosition(std::vector<double>  position) {
    //this->position = position;
    for (int k=0; k<3; k++) {
        this->position.at(k) = position.at(k);
    }
}

void Atom::setVelocity(std::vector<double>  velocity) {
    //this->velocity = velocity;
    for (int k=0; k<3; k++) {
        this->velocity.at(k) = velocity.at(k);
    }
}

void Atom::setForce(std::vector<double>  force) {
    //this->force = force;
    for (int k=0; k<3; k++) {
        this->force.at(k) = force.at(k);
    }
}

void Atom::addForce(std::vector<double>  dforce) {
    //this->force = this->force + dforce;
    for (int k=0; k<3; k++) {
        this->force.at(k) += dforce.at(k);
    }
}

void Atom::setMass(double mass) {
    this->mass = mass;
}

void Atom::setName(std::string name) {
    this->name = name;
}




