#include "eulercromer.h"
#include "../Potentials/potential.h"

using std::cout;
using std::endl;

EulerCromer::EulerCromer(real dt) : Integrator(dt) {

}

void EulerCromer::advance(const std::vector<Atom*> & atoms, int n) {
    m_potential->computeForces(atoms, n);

    /*std::vector<real> velocity{0,0,0};
    std::vector<real> position{0,0,0};
    std::vector<real> force   {0,0,0};*/

    for (int i = 0; i < n; i++) {
        /*real mass = atoms[i].getMass();
        velocity = atoms[i].getVelocity();
        position = atoms[i].getPosition();
        force    = atoms[i].getForce();*/

        for (int k=0; k<3; k++) {
            atoms.at(i)->addVelocity(m_dt/atoms.at(i)->getMass() * atoms.at(i)->getForce().at(k),k );
            atoms.at(i)->addPosition(m_dt*atoms.at(i)->getVelocity().at(k), k);
            /*atoms[i].setVelocity(velocity.at(k) + m_dt/mass * force.at(k),    k);
            atoms[i].setPosition(position.at(k) + m_dt      * velocity.at(k), k);*/

        }
    }
}

