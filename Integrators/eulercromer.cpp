#include "eulercromer.h"
#include "../Potentials/potential.h"

using std::cout;
using std::endl;

EulerCromer::EulerCromer(double dt) : Integrator(dt) {

}

void EulerCromer::advance(Atom* atoms, int n) {
    this->potential->computeForces(atoms, n);

    std::vector<double> velocity{0,0,0};
    std::vector<double> position{0,0,0};
    std::vector<double> force   {0,0,0};

    for (int i = 0; i < n; i++) {
        double mass = atoms[i].getMass();
        velocity = atoms[i].getVelocity();
        position = atoms[i].getPosition();
        force    = atoms[i].getForce();

        for (int k=0; k<3; k++) {
            velocity.at(k) += this->dt/mass * force.at(k);
            position.at(k) += this->dt      * velocity.at(k);
        }
        atoms[i].setVelocity(velocity);
        atoms[i].setPosition(position);

        /*atoms[i].setVelocity(atoms[i].getVelocity()+(dt/mass)*atoms[i].getForce());
        atoms[i].setPosition(atoms[i].getPosition()+dt*atoms[i].getVelocity());*/
    }
}

