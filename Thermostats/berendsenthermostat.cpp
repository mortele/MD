#include "berendsenthermostat.h"
//#include <tgmath.h>
#include <cmath>
#include <vector>
#include <iostream>
#include "../atom.h"
#include "../system.h"

using std::cout;
using std::endl;

BerendsenThermostat::BerendsenThermostat(System* system,
                                         real targetTemperature,
                                         real tau,
                                         real dt) :
        Thermostat(system, targetTemperature, dt) {
    m_tau = tau;
    m_dtOverTau = dt/tau;
}

void BerendsenThermostat::adjustVelocities(real instantaneousTemperature) {
    for (int i=0; i < m_system->getN(); i++) {
        real gamma = std::sqrt(1+m_dtOverTau*(m_targetTemperature/instantaneousTemperature-1));
        Atom* atom = at(m_system->getAtoms(), i);
        for (int k=0; k<3; k++) {
            atom->multiplyVelocity(gamma, k);
        }
    }
}
