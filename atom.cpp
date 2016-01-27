#include "atom.h"

Atom::Atom() {
}

Atom::Atom(std::string name, double mass) {
    m_mass     = mass;
    m_name     = name;
}

Atom::Atom(double mass) {
    m_mass     = mass;
}

void Atom::setPosition(std::vector<double>  position) {
    for (int k=0; k<3; k++) {
        m_position.at(k) = position.at(k);
    }
}

void Atom::setPosition(double x, int index) {
    m_position.at(index) = x;
}



void Atom::setVelocity(std::vector<double>  velocity) {
    for (int k=0; k<3; k++) {
        m_velocity.at(k) = velocity.at(k);
    }
}

void Atom::setVelocity(double v, int index) {
    m_velocity.at(index) = v;
}


void Atom::setForce(std::vector<double>  force) {
    for (int k=0; k<3; k++) {
        m_force.at(k) = force.at(k);
    }
}

void Atom::setForce(double f, int index) {
    m_force.at(index) = f;
}

void Atom::addForce(std::vector<double>  dforce) {
    for (int k=0; k<3; k++) {
        m_force.at(k) += dforce.at(k);
    }
}


void Atom::setMass(double mass) {
    m_mass = mass;
}

void Atom::setName(std::string name) {
    m_name = name;
}

void Atom::setCellListIndex(int cellListIndex) {
    m_cellListIndex = cellListIndex;
}




