#include "atom.h"
#include <iostream>
using std::cout; using std::endl;

int Atom::nextIndex = 0;
real_posvel *Atom::positions = nullptr;
real_posvel *Atom::velocities = nullptr;
real_posvel *Atom::forces = nullptr;

Atom::Atom(std::string name, real_posvel mass) : Atom(mass) {
    m_name     = name;
}

template <int type>
real_posvel* Atom::getNext()
{
    if(type == 0) {
        if(positions == nullptr) positions = new real_posvel[1000000];
        real_posvel* nextPosition = &positions[Atom::nextIndex];
        return nextPosition;
    }

    if(type == 1) {
        if(velocities == nullptr) velocities = new real_posvel[1000000];
        real_posvel* nextVelocity = &velocities[Atom::nextIndex];
        return nextVelocity;
    }

    if(type == 2) {
        if(forces == nullptr) forces = new real_posvel[1000000];
        real_posvel* nextForce = &forces[Atom::nextIndex];
        return nextForce;
    }
    return 0;
}

Atom::Atom(real_posvel mass) {
    m_mass     = mass;
    m_position = Atom::getNext<0>();
    m_velocity = Atom::getNext<1>();
    m_force    = Atom::getNext<2>();
    Atom::nextIndex += 3;
    m_positionLastNeighborListUpdate[0] = 1e9; // Always build neighborlist first time
    m_positionLastNeighborListUpdate[1] = 1e9;
    m_positionLastNeighborListUpdate[2] = 1e9;
}

void Atom::setPosition(real_posvel x, int index) {
    at(m_position,index) = x;
    at(m_positionUnwrapped,index) = x;
}

void Atom::setPosition(std::vector<real_posvel> x)
{
    if(x.size() < 3) {
        cout << "HOREFAEN!" << endl;
    }
    m_position[0] = x[0];
    m_position[1] = x[1];
    m_position[2] = x[2];
    m_positionUnwrapped[0] = x[0];
    m_positionUnwrapped[1] = x[1];
    m_positionUnwrapped[2] = x[2];
}

void Atom::setVelocity(std::vector<real_posvel> v)
{
    if(v.size() < 3) {
        cout << "HOREFAEN 2!" << endl;
    }
    m_velocity[0] = v[0];
    m_velocity[1] = v[1];
    m_velocity[2] = v[2];
}

void Atom::setVelocity(real_posvel v, int index) {
    at(m_velocity,index) = v;
}

void Atom::setForce(real_posvel f, int index) {
    at(m_force,index) = f;
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

bool Atom::needToUpdateNeighborList(real neighborListShellThickness)
{
    real dx = m_positionUnwrapped[0] - m_positionLastNeighborListUpdate[0];
    real dy = m_positionUnwrapped[1] - m_positionLastNeighborListUpdate[1];
    real dz = m_positionUnwrapped[2] - m_positionLastNeighborListUpdate[2];
    real dr2 = dx*dx + dy*dy + dz*dz;
    return dr2>(neighborListShellThickness)*(neighborListShellThickness);
}

void Atom::didUpdateNeighborlist()
{
    m_positionLastNeighborListUpdate[0] = m_positionUnwrapped[0];
    m_positionLastNeighborListUpdate[1] = m_positionUnwrapped[1];
    m_positionLastNeighborListUpdate[2] = m_positionUnwrapped[2];
}




