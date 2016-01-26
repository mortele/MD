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
    for (int k=0; k<3; k++) {
        this->position.at(k) = position.at(k);
    }
}

void Atom::setPosition(double x, int index) {
    this->position.at(index) = x;
}



void Atom::setVelocity(std::vector<double>  velocity) {
    for (int k=0; k<3; k++) {
        this->velocity.at(k) = velocity.at(k);
    }
}

void Atom::setVelocity(double v, int index) {
    this->velocity.at(index) = v;
}



void Atom::setForce(std::vector<double>  force) {
    for (int k=0; k<3; k++) {
        this->force.at(k) = force.at(k);
    }
}

void Atom::setForce(double f, int index) {
    this->force.at(index) = f;
}

void Atom::addForce(std::vector<double>  dforce) {
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

void Atom::setCellListIndex(int cellListIndex, int index) {
    this->cellListIndex.at(index) = cellListIndex;
}




