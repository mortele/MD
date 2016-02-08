#include "atom.h"


Atom::Atom(std::string name, real_posvel mass) {
    m_mass     = mass;
    m_name     = name;
}

Atom::Atom(real_posvel mass) {
    m_mass     = mass;
}

void Atom::setPosition(std::vector<real_posvel>  position) {
    for (int k=0; k<3; k++) {
        m_position.at(k) = position.at(k);
    }
}

void Atom::setPosition(real_posvel x, int index) {
    m_position.at(index) = x;
}



void Atom::setVelocity(std::vector<real_posvel>  velocity) {
    for (int k=0; k<3; k++) {
        m_velocity.at(k) = velocity.at(k);
    }
}

void Atom::setVelocity(real_posvel v, int index) {
    m_velocity.at(index) = v;
}


void Atom::setForce(std::vector<real_posvel>  force) {
    for (int k=0; k<3; k++) {
        m_force.at(k) = force.at(k);
    }
}

void Atom::setForce(real_posvel f, int index) {
    m_force.at(index) = f;
}

void Atom::addForce(std::vector<real_posvel>  dforce) {
    for (int k=0; k<3; k++) {
        m_force.at(k) += dforce.at(k);
    }
}


void Atom::setMass(real_posvel mass) {
    m_mass = mass;
}

void Atom::setName(std::string name) {
    m_name = name;
}

void Atom::setCellListIndex(int i, int j, int k) {
    m_cellListIndex[0] = i;
    m_cellListIndex[1] = j;
    m_cellListIndex[2] = k;
}

void Atom::setIndex(int index) {
    m_index = index;
}




