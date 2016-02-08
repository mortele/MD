#include "eulercromer.h"
#include "../Potentials/potential.h"
#include "../system.h"
#include "../atom.h"

using std::cout;
using std::endl;

EulerCromer::EulerCromer(real dt, System* system) :
        Integrator(dt, system) {

}

void EulerCromer::advance() {
    m_potential->computeForces();

    for (int i = 0; i < m_system->getN(); i++) {
        Atom* atom = at(m_system->getAtoms(),i);
        for (int k=0; k<3; k++) {
            atom->addVelocity(m_dt/atom->getMass() * at(atom->getForce(),k),k );
            atom->addPosition(m_dt*at(atom->getVelocity(),k), k);
        }
    }
}

