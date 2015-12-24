#include "eulercromer.h"

EulerCromer::EulerCromer(double dt) : Integrator(dt) {

}

void EulerCromer::advance(Atom* atoms, int n) {
    for (int i = 0; i < n; i++) {
        double mass = atoms[i].getMass();

        atoms[i].setVelocity(atoms[i].getVelocity()+(dt/mass)*atoms[i].getForce());
        atoms[i].setPosition(atoms[i].getPosition()+dt*atoms[i].getVelocity());
    }
}

