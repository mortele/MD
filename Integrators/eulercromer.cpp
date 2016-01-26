#include "eulercromer.h"
#include "../Potentials/potential.h"

using std::cout;
using std::endl;

EulerCromer::EulerCromer(double dt) : Integrator(dt) {

}

void EulerCromer::advance(const std::vector<Atom*> & atoms, int n) {
    this->potential->computeForces(atoms, n);

    /*std::vector<double> velocity{0,0,0};
    std::vector<double> position{0,0,0};
    std::vector<double> force   {0,0,0};*/

    for (int i = 0; i < n; i++) {
        /*double mass = atoms[i].getMass();
        velocity = atoms[i].getVelocity();
        position = atoms[i].getPosition();
        force    = atoms[i].getForce();*/

        for (int k=0; k<3; k++) {
            atoms.at(i)->addVelocity(this->dt/atoms.at(i)->getMass() * atoms.at(i)->getForce().at(k),k );
            atoms.at(i)->addPosition(this->dt*atoms.at(i)->getVelocity().at(k), k);
            /*atoms[i].setVelocity(velocity.at(k) + this->dt/mass * force.at(k),    k);
            atoms[i].setPosition(position.at(k) + this->dt      * velocity.at(k), k);*/

        }
    }
}

