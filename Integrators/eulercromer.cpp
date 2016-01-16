#include "eulercromer.h"
#include "../Potentials/potential.h"

using std::cout;
using std::endl;

EulerCromer::EulerCromer(double dt) : Integrator(dt) {

}

void EulerCromer::advance(Atom* atoms, int n) {
    this->potential->computeForces(atoms, n);

    for (int i = 0; i < n; i++) {
        double mass = atoms[i].getMass();
        atoms[i].setVelocity(atoms[i].getVelocity()+(dt/mass)*atoms[i].getForce());
        atoms[i].setPosition(atoms[i].getPosition()+dt*atoms[i].getVelocity());
    }
}

